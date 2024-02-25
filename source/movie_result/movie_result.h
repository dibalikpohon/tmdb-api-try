#include <stdint.h>

#include "../sds/sds.h"
#include "../stb_ds/stb_ds.h"

#ifndef _MOVIE_RESULT_S_H_
#  define _MOVIE_RESULT_S_H_

struct movie_result_s {
  int       adult;
  uint64_t *genre_ids;  // Will be backed with stb_ds
  uint64_t  id;
  sds       original_title;
  sds       overview;
  double    popularity;
  sds       release_date;
  sds       title;
  double    vote_average;
  size_t    vote_count;
};

typedef struct movie_result_s movie_t;

struct movie_result_s *movie_result_new();

void movie_result_free(struct movie_result_s *movie_result);

void movie_result_parse_from_json(struct movie_result_s   *movie_result,
                                  const struct json_object *jobj);
#endif  // !_MOVIE_RESULT_S_H_
