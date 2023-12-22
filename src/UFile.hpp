#ifndef UFILE_HPP_
#define UFILE_HPP_

#include <iostream>
#include <string>

#include "Tools.hpp"

#if defined(__clang__) || defined(__GNUC__)
#define CPP_STANDARD __cplusplus
#elif defined(_MSC_VER)
#define CPP_STANDARD _MSVC_LANG
#endif

#if CPP_STANDARD >= 201103L && CPP_STANDARD < 201703L
#include <cstring>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#endif
#if CPP_STANDARD >= 201703L
#include <filesystem>
namespace fs = std::filesystem;
#endif

class UFile {
 private:
  fs::path _p;

 public:
  explicit UFile(const std::string &path) : _p(path) {}
  explicit UFile(const fs::path &path) : _p(path) {}

  std::string path() { return _p.string(); }
};

#endif  // UFILE_HPP_
