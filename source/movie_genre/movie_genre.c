#include "movie_genre.h"

#include <curl/curl.h>
#include <curl/easy.h>
#include <stddef.h>
#include <stdint.h>

#include "../stb_ds/stb_ds.h"

struct movie_genre_hm_s *movie_genres_hm = NULL;

const struct movie_genre_s *movie_genre_get_genre(uint64_t genre_id) {
  ptrdiff_t index = hmgeti(movie_genres_hm, genre_id);

  if (index == -1) {
    return NULL;
  }

  return &((movie_genres_hm + index)->value);
}

const char *movie_genre_id_to_string(uint64_t genre_id) {
  const struct movie_genre_s *movie_genre = movie_genre_get_genre(genre_id);

  if (movie_genre == NULL) {
    return NULL;
  }

  return movie_genre->name;
}

const char **genre_multi_id_to_string(uint64_t *genre_id, size_t len) {
  const char **result = NULL;

  for (size_t i = 0; i < len; i++) {
    arrput(result, movie_genre_id_to_string(genre_id[i]));
  }

  return result;
}
