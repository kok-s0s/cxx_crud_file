#ifndef UFILE_HPP_
#define UFILE_HPP_

#include <filesystem>
#include <fstream>
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
  UFile(const char *path) { _p = path; }
  UFile(const std::string &path) { _p = path; }
  UFile(const fs::path &path) { _p = path; }
  ~UFile() {}

  fs::path handle() { return _p; }

  void setPath(const std::string &path) { _p = path; }

  void setPath(const fs::path &path) { _p = path; }

  std::string getPath() { return _p.string(); }

  std::vector<std::string> split(const std::string &data,
                                 const std::string &separator) {
    std::vector<std::string> result;
    if (data == "") return result;

    char *thisStr = new char[data.length() + 1];
    char *thisSeparator = new char[separator.length() + 1];

#if defined(_MSC_VER)
    strcpy_s(thisStr, data.length() + 1, data.c_str());
    strcpy_s(thisSeparator, separator.length() + 1, separator.c_str());

    char *next_token = NULL;
    char *token = strtok_s(thisStr, thisSeparator, &next_token);
    while (token) {
      std::string tempStr = token;
      result.push_back(tempStr);
      token = strtok_s(NULL, thisSeparator, &next_token);
    }
#elif defined(__GNUC__)
    strcpy(thisStr, data.c_str());
    strcpy(thisSeparator, separator.c_str());

    char *token = strtok(thisStr, thisSeparator);
    while (token) {
      std::string tempStr = token;
      result.push_back(tempStr);
      token = strtok(NULL, thisSeparator);
    }
#endif

    return result;
  }

  static void deleteTargetFile(std::string directoryPath, std::string fileName,
                               bool recursiveTraversal = true) {
    if (recursiveTraversal) {
      for (auto const &dir_entry :
           fs::recursive_directory_iterator(directoryPath)) {
        if (dir_entry.path().filename() == fileName) {
          remove(dir_entry.path());
        }
      }
    } else {
      for (auto const &dir_entry : fs::directory_iterator(directoryPath)) {
        if (dir_entry.path().filename() == fileName) {
          remove(dir_entry.path());
        }
      }
    }
  }

  static void copyFile(const std::string &sourceFile,
                       const std::string &targetFile,
                       const bool &overwriteFile) {
    fs::path file(targetFile);
    fs::create_directories(file.parent_path());

    if (overwriteFile && fs::exists(targetFile)) {
      fs::remove(targetFile);
    }

    const auto copyOptions =
        fs::copy_options::update_existing | fs::copy_options::recursive;

    fs::copy(sourceFile, targetFile, copyOptions);
  }

  static bool copyDirectoryFiles(const std::string &sourceDirectory,
                                 const std::string &targetDirectory,
                                 const bool &overwriteFile) {
    if (!fs::exists(sourceDirectory)) return false;

    fs::create_directories(targetDirectory);

    for (auto const &dir_entry : fs::directory_iterator(sourceDirectory)) {
      if (dir_entry.path().filename() == "." ||
          dir_entry.path().filename() == "..")
        continue;

      if (fs::is_directory(dir_entry.symlink_status())) {
        if (!copyDirectoryFiles(
                dir_entry.path().string(),
                (fs::path(targetDirectory) / dir_entry.path().filename())
                    .string(),
                overwriteFile)) {
          return false;
        }
      } else {
        if (overwriteFile &&
            fs::exists((fs::path(targetDirectory) / dir_entry.path().filename())
                           .string())) {
          fs::remove((fs::path(targetDirectory) / dir_entry.path().filename())
                         .string());
        }

        const auto copyOptions =
            fs::copy_options::update_existing | fs::copy_options::recursive;

        fs::copy(
            dir_entry.path().string(),
            (fs::path(targetDirectory) / dir_entry.path().filename()).string(),
            copyOptions);
      }
    }

    return true;
  }
};

#endif  // UFILE_HPP_
