#include <curl/curl.h>
#include <stdint.h>
#include <stdio.h>

#include "../sds/sds.h"

#ifndef _MOVIE_GENRE_H_
#  define _MOVIE_GENRE_H_

struct movie_genre_s {
  uint64_t id;
  sds      name;
};

struct movie_genre_hm_s {
  uint64_t             key;
  struct movie_genre_s value;
};


typedef struct movie_genre_s movie_genre_t;

int movie_genre_init(const char *language);

void movie_genre_deinit(void);

const struct movie_genre_s *movie_genre_get_genre(uint64_t genre_id);

const char *movie_genre_id_to_string(uint64_t genre_id);

const char **genre_multi_id_to_string(uint64_t *genre_id, size_t len);

#endif  // !_MOVIE_GENRE_H_
