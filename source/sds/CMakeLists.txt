add_library(sds STATIC)

target_sources(sds PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/sds.c
                           ${CMAKE_CURRENT_SOURCE_DIR}/sds.h)

set(sds_h
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE)
