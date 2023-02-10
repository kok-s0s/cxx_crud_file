#ifndef UFILE_HPP_
#define UFILE_HPP_

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

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

using std::ofstream;
using std::string;

class UFile {
 private:
  fs::path _p;

 public:
  UFile() {}
  UFile(string path) { _p = path; }
  UFile(fs::path& path) { _p = path; }
  ~UFile() {}
  fs::path handle() { return _p; }
};

#endif  // UFILE_HPP_