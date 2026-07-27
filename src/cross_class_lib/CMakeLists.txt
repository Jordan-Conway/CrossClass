add_library(cross_class_lib SHARED)

target_sources(cross_class_lib
    PRIVATE
    src/data_parser.c
    src/parsers/class_data_parser.c
    src/tokens.c
    src/version.c
    PUBLIC
    includes/class_info.h
    includes/data_parser.h
    includes/field.h
    includes/linked_list.h
    includes/tokens.h
    includes/parsers/class_data_parser.h)

target_include_directories(
    cross_class_lib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(
    cross_class_lib
    PRIVATE
    ccx_reader
)

set_target_properties(cross_class_lib PROPERTIES PREFIX "")
