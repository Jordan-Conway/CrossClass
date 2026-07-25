add_library(ccx_reader_tests SHARED)

target_sources(ccx_reader_tests
    PRIVATE
    ccx_reader_tests.c
    ccx_line_data_tests.c
    PUBLIC
    ccx_reader_tests.h
    ccx_line_data_tests.h)

target_link_libraries(ccx_reader_tests
    PRIVATE
    ccx_reader)
