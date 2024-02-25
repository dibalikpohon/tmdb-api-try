#include <stdint.h>

#include "../sds/sds.h"
#include <cstdlib>

struct movie_genre_s {
  uint64_t id;
  sds      name;
};

typedef struct movie_genre_s movie_genre_t;

