#ifndef UFILE_HPP_
#define UFILE_HPP_

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#if defined(__clang__) || defined(__GNUC__)
#define CPP_STANDARD __cplusplus
#elif defined(_MSC_VER)
#define CPP_STANDARD _MSVC_LANG
#endif

#if CPP_STANDARD >= 201103L && CPP_STANDARD < 201703L
namespace fs = std::tr2::sys;
#endif
#if CPP_STANDARD >= 201703L
namespace fs = std::filesystem;
#endif

class UFile {
 private:
  fs::path _p;

 public:
  UFile() {}
  explicit UFile(const char *path) : _p(path) {}
  explicit UFile(const std::string &path) : _p(path) {}
  explicit UFile(const fs::path &path) : _p(path) {}
  ~UFile() {}

  fs::path handle() { return _p; }

  void setPath(const std::string &path) { _p = path; }

  void setPath(const fs::path &path) { _p = path; }

  std::string getPath() { return _p.string(); }

  std::vector<std::string> split(const std::string &data,
                                 const std::string &separator) {
    std::vector<std::string> result;
    if (data == "") return result;

#if defined(_MSC_VER)
    char *next_token = NULL;
    char *token =
        strtok_s((char *)data.c_str(), separator.c_str(), &next_token);
    while (token) {
      result.push_back(token);
      token = strtok_s(NULL, separator.c_str(), &next_token);
    }
#elif defined(__GNUC__)
    char *token = strtok((char *)data.c_str(), separator.c_str());
    while (token) {
      result.push_back(token);
      token = strtok(NULL, separator.c_str());
    }
#endif

    return result;
  }
};

#endif  // UFILE_HPP_
