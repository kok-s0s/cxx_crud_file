#ifndef TOOLS_HPP_
#define TOOLS_HPP_

#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string &data,
                               const std::string &separator) {
  std::vector<std::string> result;
  std::stringstream ss(data);
  std::string item;
  while (std::getline(ss, item, separator[0])) {
    result.push_back(item);
  }
  return result;
}

#endif  // TOOLS_HPP_
