#ifndef TXTFILE_HPP_
#define TXTFILE_HPP_

#include <fstream>

#include "UFile.hpp"

class TxtFile : public UFile {
 private:
  std::string _data;

 public:
  explicit TxtFile(const std::string& path) : UFile(path) {}
  explicit TxtFile(const fs::path& path) : UFile(path) {}

  std::string getData() const { return _data; }

  void setData(const std::string& data) { _data = data; }

  bool readData() {
    std::ifstream file(path());
    if (!file) {
      return false;
    }

    _data.assign((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());

    file.close();
    return true;
  }

  bool writeData() {
    std::ofstream file(path());
    if (!file) {
      return false;
    }

    file << _data;
    return true;
  }

  bool appendWriteData(const std::string& data) {
    std::ofstream file(path(), std::ios_base::app);
    if (!file) {
      return false;
    }

    file << data;
    return true;
  }
};

#endif  // TXTFILE_HPP_
