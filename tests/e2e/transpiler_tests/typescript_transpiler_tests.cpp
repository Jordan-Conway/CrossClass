#include "./typescript_transpiler_tests.hpp"
#include "transpiler_execution.hpp"
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

bool test_typescript_transpiles_correctly(std::string test_case);

const std::string test_data_directory_path = "./tests/e2e/test_data/";
const std::string ccd_file_extension = ".ccd";
const std::string typescript_file_extension = ".ts";
const std::vector<std::string> test_data{"Person"};

std::unique_ptr<TestResult> execute_typescript_tests() {
  auto result = std::make_unique<TestResult>();

  for (std::string test_case : test_data) {
    std::string test_name = "test_typescript_transpiles_correctly_" + test_case;
    bool success = test_typescript_transpiles_correctly(test_case);
    if (success) {
      result->add_succeeded_test(test_case);
    } else {
      result->add_failed_tests(test_name);
    }
  }

  return result;
}

bool test_typescript_transpiles_correctly(std::string test_case) {
  std::string input_file =
      test_data_directory_path + "input/" + test_case + ccd_file_extension;
  std::cout << "Input file is " << input_file << "\n";

  std::string output_file = test_data_directory_path + "output/" + test_case +
                            typescript_file_extension;

  int transpile_result = execute_typescript_transpiler(input_file, output_file);

  if (transpile_result != 0) {
    std::cout << "Transpilation failed for test case: " << test_case << "\n";
    return false;
  }

  std::string expected_file = test_data_directory_path + "expected/" +
                              test_case + typescript_file_extension;

  std::ifstream actual_data(output_file);
  std::ifstream expected_data(expected_file);

  std::string actual_line;
  std::string expected_line;
  int line_count = 0;

  while (std::getline(actual_data, actual_line) &&
         std::getline(expected_data, expected_line)) {
    line_count++;
    if (actual_line == expected_line) {
      continue;
    }

    std::cout << "Error: " << output_file << "differs from " << expected_file
              << " at line " << line_count << "\n";
    return false;
  }

  return true;
}