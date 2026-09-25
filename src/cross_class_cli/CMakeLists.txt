add_executable(cross_class_cli)

target_sources(cross_class_cli
    PRIVATE
    shared_macros.h
    commands/command.h
    commands/command.c
    commands/command_list.h
    commands/command_list.c
    commands/help_command/help_command.h
    commands/help_command/help_command.c
    commands/list_transpilers_command/list_transpilers_command.h
    commands/list_transpilers_command/list_transpilers_command.c
    commands/parse_file_command/parse_file_command.h
    commands/parse_file_command/parse_file_command.c
    commands/version_command/version_command.h
    commands/version_command/version_command.c
    PUBLIC
    main.c)

target_link_libraries(cross_class_cli
    PRIVATE
    ccx_reader
    cross_class_lib
)
