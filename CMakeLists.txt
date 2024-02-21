cmake_minimum_required(VERSION 3.21)

include(cmake/prelude.cmake)

project(
    tmdb-api-try
    VERSION 0.1.0
    DESCRIPTION "Short description"
    HOMEPAGE_URL "https://example.com/"
    LANGUAGES C
)

include(cmake/variables.cmake)

# ---- Declare library ----

add_library(
    tmdb-api-try_lib OBJECT
    source/lib.c
)

target_include_directories(
    tmdb-api-try_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
)

target_compile_features(tmdb-api-try_lib PUBLIC c_std_99)

# ---- Declare executable ----

add_executable(tmdb-api-try_exe source/main.c)
add_executable(tmdb-api-try::exe ALIAS tmdb-api-try_exe)

set_property(TARGET tmdb-api-try_exe PROPERTY OUTPUT_NAME tmdb-api-try)

target_compile_features(tmdb-api-try_exe PRIVATE c_std_99)

target_link_libraries(tmdb-api-try_exe PRIVATE tmdb-api-try_lib)

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
