#include "../movie_result/movie_result.h"
#include "../sds/sds.h"

#ifndef _SEARCH_MOVIE_RESULT_H_
#  define _SEARCH_MOVIE_RESULT_H_

struct search_movie_result_s {
  size_t                  page;
  size_t                  total_page;
  size_t                  total_results;
  struct movie_result_s **results;  // will be backed with stb_ds
};

typedef struct search_movie_result_s search_movie_result_t;

struct search_movie_result_s *search_movie_result_new();

void search_movie_result_free(struct search_movie_result_s **result_p);

void search_movie_result_parse_from_json(
    struct search_movie_result_s **search_movie_result_p,
    const struct json_object      *jobj);

#endif  // !_SEARCH_MOVIE_RESULT_H_
