#include <json-c/json_object.h>
#include <stdint.h>

#include "movie_result.h"

static uint64_t *parse_genre_ids_array(
    const struct json_object *genre_ids_object);

void movie_result_parse_from_json(struct movie_result_s   *movie_result,
                                  const struct json_object *jobj)
{
  struct json_object *adult_json_object = NULL;
  json_object_object_get_ex(jobj, "adult", &adult_json_object);
  movie_result->adult = json_object_get_boolean(adult_json_object);

  struct json_object *genre_ids_object = NULL;
  json_object_object_get_ex(jobj, "genre_ids", &genre_ids_object);
  movie_result->genre_ids = parse_genre_ids_array(genre_ids_object);

  struct json_object *id_object = NULL;
  json_object_object_get_ex(jobj, "id", &id_object);
  movie_result->id = json_object_get_uint64(id_object);

  struct json_object *original_title_object = NULL;
  json_object_object_get_ex(jobj, "original_title", &original_title_object);
  movie_result->original_title =
      sdsnewlen(json_object_get_string(original_title_object),
                json_object_get_string_len(original_title_object));

  struct json_object *overview_object = NULL;
  json_object_object_get_ex(jobj, "overview", &overview_object);
  movie_result->overview =
      sdsnewlen(json_object_get_string(overview_object),
                json_object_get_string_len(overview_object));

  struct json_object *popularity_object = NULL;
  json_object_object_get_ex(jobj, "popularity", &popularity_object);
  movie_result->popularity = json_object_get_double(popularity_object);

  struct json_object *release_date_object = NULL;
  json_object_object_get_ex(jobj, "release_date", &release_date_object);
  movie_result->release_date =
      sdsnewlen(json_object_get_string(release_date_object),
                json_object_get_string_len(release_date_object));

  struct json_object *title_object = NULL;
  json_object_object_get_ex(jobj, "title", &title_object);
  movie_result->title = sdsnewlen(json_object_get_string(title_object),
                                  json_object_get_string_len(title_object));

  struct json_object *vote_average_object = NULL;
  json_object_object_get_ex(jobj, "vote_average", &vote_average_object);
  movie_result->vote_average = json_object_get_double(vote_average_object);

  struct json_object *vote_count_object = NULL;
  json_object_object_get_ex(jobj, "vote_count", &vote_count_object);
  movie_result->vote_count = json_object_get_uint64(vote_count_object);

  // free allocated json object
  json_object_put(adult_json_object);
  json_object_put(genre_ids_object);
  json_object_put(id_object);
  json_object_put(original_title_object);
  json_object_put(overview_object);
  json_object_put(popularity_object);
  json_object_put(release_date_object);
  json_object_put(title_object);
  json_object_put(vote_average_object);
  json_object_put(vote_count_object);
}

static uint64_t *parse_genre_ids_array(
    const struct json_object *genre_ids_object)
{
  size_t array_length = json_object_array_length(genre_ids_object);

  uint64_t *genre_ids = NULL;
  arrsetlen(genre_ids, array_length);

  for (size_t i = 0; i < array_length; i++) {
    struct json_object *genre_id_o =
        json_object_array_get_idx(genre_ids_object, i);
    uint64_t genre_id = json_object_get_uint64(genre_id_o);
    arrput(genre_ids, genre_id);
  }

  return genre_ids;
}
