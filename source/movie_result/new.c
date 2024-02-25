#include <stdlib.h>

#include "movie_result.h"

struct movie_result_s *movie_result_new()
{
  struct movie_result_s *result = malloc(sizeof(struct movie_result_s));
  result->adult = 0;
  result->genre_ids = NULL;
  result->id = 0;
  result->original_title = NULL;
  result->overview = NULL;
  result->popularity = 0.;
  result->release_date = NULL;
  result->title = NULL;
  result->vote_average = 0.;
  result->vote_count = 0;

  return result;
}

void movie_result_free(struct movie_result_s **result_p) {
  if (result_p == NULL) { return; }
  struct movie_result_s *result = *result_p; 
  if (result == NULL) { return; }

  result->adult = 0;

  arrfree(result->genre_ids);
  result->genre_ids = NULL;
  
  result->id = 0;
  
  sdsfree(result->original_title);
  result->original_title = NULL;

  sdsfree(result->overview);
  result->overview = NULL;

  result->popularity = 0.;

  sdsfree(result->release_date);
  result->release_date = NULL;

  sdsfree(result->title);
  result->title = NULL;

  result->vote_average = 0.;
  result->vote_count = 0;

  free(result);
}
