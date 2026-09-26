#include "./includes/transpiler_execution.hpp"

#include "./execute.hpp"
#include <vector>

int execute_typescript_transpiler(std::string input_file_path,
                                  std::string output_file_path) {

  auto args = std::vector<std::string>{"ts", input_file_path, output_file_path};

  return execute_program("./bin/cross_class_cli", args);
}