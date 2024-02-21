install(
    TARGETS tmdb-api-try_exe
    RUNTIME COMPONENT tmdb-api-try_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
