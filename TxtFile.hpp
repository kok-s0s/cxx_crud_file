#ifndef TXTFILE_HPP_
#define TXTFILE_HPP_

#include <fstream>

#include "UFile.hpp"

class TxtFile : public UFile {
 private:
  std::string _data = "";

 public:
  TxtFile() {}
  explicit TxtFile(const char* path) : UFile(path) {}
  explicit TxtFile(const std::string& path) : UFile(path) {}
  explicit TxtFile(const fs::path& path) : UFile(path) {}
  ~TxtFile() {}

  std::string getData() { return _data; }

  void setData(const std::string& data) { _data = data; }

  bool readData() {
    std::fstream file;

    file.open(getPath(), std::ios::in);

    if (file.is_open()) {
      std::istreambuf_iterator<char> beg(file), end;
      std::string str(beg, end);
      _data = str;

      file.close();
      return true;
    } else {
      file.close();
      return false;
    }
  }

  bool writeData() {
    std::fstream file;

    file.open(getPath(), std::ios::out);

    if (file.is_open()) {
      file << _data;

      file.close();
      return true;
    } else {
      file.close();
      return false;
    }
  }

  bool appendWriteData(const std::string& data) {
    std::fstream file;

    file.open(getPath(), std::ios_base::app);

    if (file.is_open()) {
      file << data;

      file.close();
      return true;
    } else {
      file.close();
      return false;
    }
  }
};

#endif  // TXTFILE_HPP_
