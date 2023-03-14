#ifndef TXTFILE_HPP_
#define TXTFILE_HPP_

#include <fstream>

#include "UFile.hpp"

class TxtFile : public UFile {
 private:
  std::string _data = "";
  std::fstream file;

 public:
  TxtFile() {}
  TxtFile(const char* path) : UFile(path) {}
  TxtFile(const std::string& path) : UFile(path) {}
  TxtFile(const fs::path& path) : UFile(path) {}
  ~TxtFile() {}

  bool readData() {
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

  bool appendWriteData(const std::string data) {
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

  std::string getData() { return _data; }

  void setData(std::string data) { _data = data; }
};

#endif  // TXTFILE_HPP_
