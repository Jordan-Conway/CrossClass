#include "./typescript_transpiler_tests.hpp"
#include <iostream>
#include <string>

int main() {
  auto result = execute_typescript_tests();

  std::cout << "Succeeded: " << result->get_succeeded_test_count() << " out of "
            << result->get_total_test_count() << "\n";

  std::cout << "Failed: " << result->get_failed_test_count() << "\n";

  for (std::string failed_test : result->get_failed_tests()) {
    std::cout << failed_test << "\n";
  }

  return result->get_failed_test_count() > 0 ? 1 : 0;
}