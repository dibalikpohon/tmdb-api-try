#include <curl/curl.h>
#include <curl/easy.h>
#include <json-c/json_object.h>
#include <json-c/json_tokener.h>
#include <stdio.h>
#include <stdlib.h>

#include "../sds/sds.h"
#include "../stb_ds/stb_ds.h"
#include "movie_genre.h"

extern struct movie_genre_hm_s *movie_genres_hm;
extern void movie_genre_s_parse_from_json(struct movie_genre_s     *movie_genre,
                                          const struct json_object *jobj);

extern CURL *curl;

const struct movie_genre_hm_s movie_genre_hm_empty = {
    .key = 0, .value = {.id = 0, .name = (char *)0}};

static size_t data_response_write(char  *ptr,
                                  size_t size,
                                  size_t nmemb,
                                  void  *userdata);

int movie_genre_init(const char *language)
{
  const char *url_format =
      "https://api.themoviedb.org/3/genre/movie/list?language=%s";

  char *data_response = NULL;

  char *language_escaped = curl_easy_escape(curl, language, 0);
  sds   formatted_url    = sdscatfmt(sdsempty(), url_format, language_escaped);

  const char *auth_header_head = "Authorization: Bearer ";
  const char *auth_token       = getenv("TMDB_AUTH_TOKEN");
  sds         auth_header      = sdscat(sdsnew(auth_header_head), auth_token);

  struct curl_slist *header_list = curl_slist_append(NULL, auth_header);
  sdsfree(auth_header);

  if (header_list == NULL) {
    return -2;
  }

  {
    struct curl_slist *temp_list =
        curl_slist_append(header_list, "accept: application/json");
    if (temp_list == NULL) {
      return -2;
    }
    header_list = temp_list;
  }

  curl_easy_setopt(curl, CURLOPT_URL, formatted_url);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &data_response);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &data_response_write);
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
  CURLcode result = curl_easy_perform(curl);

  if (result != CURLE_OK) {
    return 1;
  }

  struct json_tokener *tokener = json_tokener_new();
  struct json_object  *object =
      json_tokener_parse_ex(tokener, data_response, arrlen(data_response));

  struct json_object *results = NULL;
  json_object_object_get_ex(object, "genres", &results);
  size_t genres_length = json_object_array_length(results);

  for (size_t i = 0; i < genres_length; i++) {
    struct json_object  *genre = json_object_array_get_idx(results, i);
    struct movie_genre_s movie_genre;
    movie_genre_s_parse_from_json(&movie_genre, genre);
    hmput(movie_genres_hm, movie_genre.id, movie_genre);
  }

  // set default value when get does not find the value
  hmdefaults(movie_genres_hm, movie_genre_hm_empty);

  json_object_put(results);
  json_tokener_free(tokener);
  curl_slist_free_all(header_list);
  sdsfree(formatted_url);
  curl_free(language_escaped);
  arrfree(data_response);

  return 0;
}

void movie_genre_deinit(void) {
  hmfree(movie_genres_hm);
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
