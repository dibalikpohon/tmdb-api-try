cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    tmdb-api-try
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

# list(APPEND CMAKE_PREFIX_PATH /home/karuntos/curl8)
include(cmake/variables.cmake)

find_package(json-c CONFIG)
find_package(CURL REQUIRED)

add_subdirectory(source/sds)
add_subdirectory(source/stb_ds)
add_subdirectory(source/movie_result)
add_subdirectory(source/search_movie_result)
add_subdirectory(source/movie_genre)


# ---- Declare executable ----

add_executable(tmdb-api-try_exe source/main.c)
add_executable(tmdb-api-try::exe ALIAS tmdb-api-try_exe)

set_property(TARGET tmdb-api-try_exe PROPERTY OUTPUT_NAME tmdb-api-try)

target_compile_features(tmdb-api-try_exe PRIVATE c_std_99)

target_link_libraries(tmdb-api-try_exe PRIVATE json-c::json-c)
target_link_libraries(tmdb-api-try_exe PRIVATE ${CURL_LIBRARIES})
target_link_libraries(tmdb-api-try_exe PRIVATE $<TARGET_OBJECTS:sds>)
target_link_libraries(tmdb-api-try_exe PRIVATE $<TARGET_OBJECTS:movie_result>)
target_link_libraries(tmdb-api-try_exe PRIVATE $<TARGET_OBJECTS:search_movie_result>)
target_link_libraries(tmdb-api-try_exe PRIVATE $<TARGET_OBJECTS:movie_genre>)

target_include_directories(tmdb-api-try_exe PRIVATE ${sds_h})
target_include_directories(tmdb-api-try_exe PRIVATE ${stb_ds_h})

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT tmdb-api-try_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of tmdb-api-try"
  )
endif()

include(cmake/dev-mode.cmake)
