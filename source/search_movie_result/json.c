#include <json-c/json_object.h>

#include "search_movie_result.h"

static struct movie_result_s **parse_movie_results_array(
    const struct json_object *movie_results_object);

void search_movie_result_parse_from_json(
    struct search_movie_result_s *search_movie_result,
    const struct json_object      *jobj)
{
  struct json_object *page_object = NULL;
  json_object_object_get_ex(page_object, "page", &page_object);
  search_movie_result->page = json_object_get_uint64(page_object);

  struct json_object *total_page_object = NULL;
  json_object_object_get_ex(jobj, "total_page", &total_page_object);
  search_movie_result->total_page = json_object_get_uint64(total_page_object);

  struct json_object *total_results_object = NULL;
  json_object_object_get_ex(jobj, "total_results", &total_results_object);
  search_movie_result->total_results =
      json_object_get_uint64(total_results_object);

  struct json_object *results_object = NULL;
  json_object_object_get_ex(jobj, "results", &results_object);
  search_movie_result->results = parse_movie_results_array(results_object);
}

static struct movie_result_s **parse_movie_results_array(
    const struct json_object *movie_results_object)
{
  size_t array_length = json_object_array_length(movie_results_object);

  struct movie_result_s **movie_results = NULL;
  arrsetlen(movie_results, array_length);

  for (size_t i = 0; i < array_length; i++) {
    struct json_object *movie_result_o =
        json_object_array_get_idx(movie_results_object, i);
    struct movie_result_s *movie_result = movie_result_new();
    movie_results[i]                    = movie_result;
    movie_result_parse_from_json(movie_results[i], movie_result_o);
  }

  return movie_results;
}
