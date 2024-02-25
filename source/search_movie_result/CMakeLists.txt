add_library(search_movie_result OBJECT)

target_sources(search_movie_result PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/new.c
                                           ${CMAKE_CURRENT_SOURCE_DIR}/json.c)

set(search_movie_result_h
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
