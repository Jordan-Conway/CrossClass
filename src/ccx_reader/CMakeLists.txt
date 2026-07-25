add_library(ccx_reader SHARED)

target_sources(ccx_reader
    PRIVATE
    src/ccx_reader.c
    src/ccx_line_data.c
    PUBLIC
    includes/ccx_reader.h
    includes/ccx_line_data.h)

target_include_directories(
    ccx_reader
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes)

set_target_properties(ccx_reader PROPERTIES PREFIX "")
