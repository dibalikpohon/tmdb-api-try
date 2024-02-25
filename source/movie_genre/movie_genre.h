#include <stdint.h>

#include "../sds/sds.h"
#include <cstdlib>

struct movie_genre_s {
  uint64_t id;
  sds      name;
};

typedef struct movie_genre_s movie_genre_t;

struct movie_genre_s *movie_genre_new(); 

void movie_genre_free(struct movie_genre_s **result_p) {

}
