# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(tmdb-api-tryTests LANGUAGES C)

# ---- Tests ----

add_executable(tmdb-api-try_test source/tmdb-api-try_test.c)
target_link_libraries(tmdb-api-try_test PRIVATE tmdb-api-try_lib)
target_compile_features(tmdb-api-try_test PRIVATE c_std_99)

add_test(NAME tmdb-api-try_test COMMAND tmdb-api-try_test)

# ---- End-of-file commands ----

add_folders(Test)
