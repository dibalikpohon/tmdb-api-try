add_library(movie_genre OBJECT)

target_sources(
  movie_genre
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/init.c ${CMAKE_CURRENT_SOURCE_DIR}/json.c
          ${CMAKE_CURRENT_SOURCE_DIR}/movie_genre.c)

set(movie_genre_h ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
