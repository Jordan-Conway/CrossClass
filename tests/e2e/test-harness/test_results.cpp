#include "./test_results.hpp"
#include <string>
#include <vector>

TestResult::TestResult() {
  failed_tests = std::vector<std::string>{};
  succeeded_tests = std::vector<std::string>{};
}

int TestResult::get_total_test_count() {
  return this->get_succeeded_test_count() + this->get_failed_test_count();
}

int TestResult::get_succeeded_test_count() { return succeeded_tests.size(); }

int TestResult::get_failed_test_count() { return failed_tests.size(); }

const std::vector<std::string> TestResult::get_failed_tests() {
  return failed_tests;
}

void TestResult::add_failed_tests(std::string test_name) {
  failed_tests.push_back(test_name);
}

void TestResult::add_succeeded_test(std::string test_name) {
  succeeded_tests.push_back(test_name);
}