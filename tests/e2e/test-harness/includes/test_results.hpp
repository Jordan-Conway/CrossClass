#ifndef CROSS_CLASS_E2E_TEST_RESULT
#define CROSS_CLASS_E2E_TEST_RESULT

#include <string>
#include <vector>

class TestResult {
private:
  std::vector<std::string> failed_tests;
  std::vector<std::string> succeeded_tests;
  int success_count;

public:
  TestResult();
  int get_total_test_count();
  int get_succeeded_test_count();
  int get_failed_test_count();
  const std::vector<std::string> get_failed_tests();
  void add_failed_tests(std::string test_name);
  void add_succeeded_test(std::string test_name);
};

#endif