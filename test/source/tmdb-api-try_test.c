#include <string.h>

#include "lib.h"

int main(int argc, char const* argv[])
{
  struct library lib = create_library();

  (void)argc;
  (void)argv;

  return strcmp(lib.name, "tmdb-api-try") == 0 ? 0 : 1;
}
