#include <json-c/json_object.h>
#include <json-c/json_types.h>
#include <stdio.h>
#include <stdlib.h>

#include "../sds/sds.h"
#include "../stb_ds/stb_ds.h"
#include "movie_genre.h"

void movie_genre_s_parse_from_json(struct movie_genre_s     *movie_genre,
                                   const struct json_object *jobj)
{
  struct json_object *id_object = NULL;
  json_object_object_get_ex(jobj, "id", &id_object);
  movie_genre->id = json_object_get_uint64(id_object);

  struct json_object *name_object = NULL;
  json_object_object_get_ex(jobj, "name", &name_object);
  movie_genre->name = sdsnewlen(json_object_get_string(name_object),
                                json_object_get_string_len(name_object));
}
