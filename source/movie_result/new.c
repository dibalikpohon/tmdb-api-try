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

void movie_result_free(struct movie_result_s *movie_result) {
  if (movie_result == NULL) { return; }

  movie_result->adult = 0;

  arrfree(movie_result->genre_ids);
  movie_result->genre_ids = NULL;
  
  movie_result->id = 0;
  
  sdsfree(movie_result->original_title);
  movie_result->original_title = NULL;

  sdsfree(movie_result->overview);
  movie_result->overview = NULL;

  movie_result->popularity = 0.;

  sdsfree(movie_result->release_date);
  movie_result->release_date = NULL;

  sdsfree(movie_result->title);
  movie_result->title = NULL;

  movie_result->vote_average = 0.;
  movie_result->vote_count = 0;

  free(movie_result);
}
