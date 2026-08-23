add_executable(cross_class_cli)

target_sources(cross_class_cli
    PRIVATE
    commands/command.c
    commands/command_list.c
    commands/help_command/help_command.c
    commands/version_command/version_command.c
    commands/parse_file_command/parse_file_command.c
    PUBLIC
    main.c)

target_link_libraries(cross_class_cli
    PRIVATE
    ccx_reader
    cross_class_lib
)

target_compile_options(cross_class_cli PRIVATE -Wall -Wextra -Werror -Wpedantic)
