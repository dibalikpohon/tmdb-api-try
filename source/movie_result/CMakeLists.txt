add_library(movie_result OBJECT)

target_sources(movie_result PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/json.c
                                    ${CMAKE_CURRENT_SOURCE_DIR}/new.c)

set(movie_result_h
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
