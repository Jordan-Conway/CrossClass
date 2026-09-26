#include "./execute.hpp"

#include <cstdlib>
#include <format>
#include <iostream>
#include <numeric>
#include <vector>

std::string join(std::vector<std::string> args);

int execute_program(const std::string path,
                    const std::vector<std::string> args) {
  std::string all_args = join(args);
  auto command = std::format("{} {}", path, all_args);

  std::cout << "Executing: " << command << "\n";

  return std::system(command.c_str());
}

/**
Returns a string consisting of every element in args joined with a whitespace
*/
std::string join(std::vector<std::string> args) {
  return std::accumulate(
      args.begin(), args.end(), std::string(),
      [](const std::string &a, const std::string &b) -> std::string {
        return a + (a.length() > 0 ? " " : "") + b;
      });
}