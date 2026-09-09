add_library(cross_class_lib_tests SHARED)

target_sources(cross_class_lib_tests
    PRIVATE
    cross_class_lib_tests.c
    data_parser_tests/data_parser_tests.h
    data_parser_tests/data_parser_tests.c
    data_parser_tests/class_data_parser_tests/class_data_parser_tests.h
    data_parser_tests/class_data_parser_tests/class_data_parser_tests.c
    version_tests/version_tests.h
    version_tests/version_tests.c
    PUBLIC
    cross_class_lib_tests.h
)

target_link_libraries(cross_class_lib_tests
    PRIVATE
    ccx_reader
    cross_class_lib)
