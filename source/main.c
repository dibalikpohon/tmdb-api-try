#include <curl/curl.h>
#include <curl/easy.h>
#include <json-c/json.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "movie_result/movie_result.h"
#include "sds/sds.h"
#include "search_movie_result/search_movie_result.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds/stb_ds.h"

#define MAX_SEARCH_INPUT 120
#define MAX_URL_LENGTH   480

size_t data_response_write(char  *ptr,
                           size_t size,
                           size_t nmemb,
                           void  *userdata);

int main(int argc, char const *argv[])
{
  (void)argc, (void)argv;

  (void)fputs("What you want?", stdout);

  int errcode = 0;

  const char *url_format =
      "https://api.themoviedb.org/3/search/"
      "movie?query=%s&include_adult=false&language=en-US&page=1";

  char *data_response = NULL;

  char *search_input = malloc(sizeof(char) * MAX_SEARCH_INPUT);
  {
    char *inputted = fgets(search_input, MAX_SEARCH_INPUT, stdin);
    if (inputted == NULL) {
      puts("Aww, just a small failure.");
      errcode = -1;
      goto cleanup_5;
    }
    search_input = inputted;
  }

  CURL *curl = curl_easy_init();
  if (!curl) {
    puts("Awwie, CURL cannot init!");

    errcode = -2;
    goto cleanup_6;
  }

  // remove the newline of the fgets
  search_input[strlen(search_input) - 1] = 0;

  char *search_input_escape = curl_easy_escape(curl, search_input, 0);

  sds formatted_url = sdscatfmt(sdsempty(), url_format, search_input_escape);

  const char        *auth_header_head = "Authorization: Bearer ";
  const char        *auth_token       = getenv("TMDB_AUTH_TOKEN");
  sds                auth_header = sdscat(sdsnew(auth_header_head), auth_token);

  struct curl_slist *header_list = curl_slist_append(NULL, auth_header);
  sdsfree(auth_header);
  if (header_list == NULL) {
    puts("ono, something happened!");
    errcode = -2;
    goto cleanup_7;
  }

  {
    struct curl_slist *temp_list =
        curl_slist_append(header_list, "accept: application/json");
    if (temp_list == NULL) {
      puts("ono, something happened!");
      errcode = -2;
      goto cleanup_7;
    }
    header_list = temp_list;
  }

  curl_easy_setopt(curl, CURLOPT_URL, formatted_url);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data_response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_response_write);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

  puts("Please wait while we are searching for you, you lazy shrek...");
  CURLcode result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    puts("Haiyaa, cURL is a failure");
    puts(curl_easy_strerror(result));
    errcode = 1;

    goto cleanup_8;
  }

  struct json_tokener *tokener = json_tokener_new();
  struct json_object  *object =
      json_tokener_parse_ex(tokener, data_response, arrlen(data_response));

  if (object == NULL) {
    puts("I'm sorry. The response seems to be freaking today.");
    enum json_tokener_error err = json_tokener_get_error(tokener);
    puts(json_tokener_error_desc(err));

    errcode = 2;

    goto cleanup_9;
  }

  if (!json_object_is_type(object, json_type_object)) {
    puts("Huh? It's not an object?");
    errcode = 3;

    goto cleanup_10;
  }

  struct search_movie_result_s *search_movie_result = search_movie_result_new();
  search_movie_result_parse_from_json(search_movie_result, object);

  puts("Here are some results of your search:");
  printf("Page: %zu\n", search_movie_result->page);
  printf("Total page: %zu\n", search_movie_result->total_page);
  printf("Total results: %zu movies\n", search_movie_result->total_results);

  size_t result_len = arrlenu(search_movie_result->results);
  printf("There are %zu items in the current page:\n", result_len);

  for (size_t i = 0; i < result_len; i++) {
    struct movie_result_s *movie_result = search_movie_result->results[i];
    printf("=====%s=====\n", movie_result->title);
    printf("* Original Title: %s\n", movie_result->original_title);
    printf("* Overview: %s\n", movie_result->overview);
    printf("* Release date: %s\n", movie_result->release_date);
    printf("* Popularity: %lf\n", movie_result->popularity);
    printf("* Vote average: %lf\n", movie_result->vote_average);
    printf("* Vote count: %zu\n", movie_result->vote_count);
    printf("* Is this adult movie? %s\n",
           movie_result->adult == 1 ? "yes" : "no");
    puts("");
  }

  puts("i'm done");

  search_movie_result_free(search_movie_result);

cleanup_10:
  json_object_put(object);

cleanup_9:
  json_tokener_free(tokener);

cleanup_8:
  curl_easy_cleanup(curl);
  arrfree(data_response);

cleanup_7:
  curl_slist_free_all(header_list);
  curl_free(search_input_escape);

cleanup_6:
  sdsfree(formatted_url);

cleanup_5:
  free(search_input);

  return errcode;
}

size_t data_response_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  char  *data      = *(char **)userdata;
  size_t real_size = nmemb * size;

  char *data_ret = arraddnptr(data, real_size);
  memcpy(data_ret, ptr, real_size);

  *(char **)userdata = data;

  return real_size;
}
