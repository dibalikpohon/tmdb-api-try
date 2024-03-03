#include <stdlib.h>

#include "../movie_result/movie_result.h"
#include "../stb_ds/stb_ds.h"
#include "search_movie_result.h"

struct search_movie_result_s *search_movie_result_new()
{
  struct search_movie_result_s *result =
      malloc(sizeof(struct search_movie_result_s));
  result->page          = 0;
  result->total_page    = 0;
  result->total_results = 0;
  result->results       = NULL;
  return result;
};

void search_movie_result_free(struct search_movie_result_s *search_movie_result)
{
  search_movie_result->page          = 0;
  search_movie_result->total_page    = 0;
  search_movie_result->total_results = 0;

  // free all lists of result
  size_t results_len = arrlenu(search_movie_result->results);
  for (size_t i = 0; i < results_len; i++) {
    movie_result_free(search_movie_result->results[i]);
  }
  arrfree(search_movie_result->results);

  search_movie_result->results = NULL;

  free(search_movie_result);
}
