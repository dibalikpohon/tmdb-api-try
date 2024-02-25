#include <stdint.h>
#include <stdio.h>

#include "../sds/sds.h"

struct movie_genre_s {
  uint64_t id;
  sds      name;
};

typedef struct movie_genre_s movie_genre_t;

