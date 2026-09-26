#include <iostream>
#include <vector>

#include "./execute.hpp"

int main() {
  std::cout << "Hello World!\n";

  auto args = std::vector<std::string>{"ts", "./Examples/Person.ccd",
                                       "./Examples/Person.ts"};
  execute_program("./bin/cross_class_cli", args);

  return 0;
}