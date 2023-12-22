#ifndef BINFILE_HPP_
#define BINFILE_HPP_

#include <fstream>
#include <vector>

#include "UFile.hpp"

class BinFile : public UFile {
 private:
  std::vector<uint8_t> _data;
  int _length = 0;

 public:
  explicit BinFile(const std::string &path) : UFile(path) {}
  explicit BinFile(const fs::path &path) : UFile(path) {}

  void setData(const std::vector<uint8_t> &data) { _data = data; }

  std::vector<uint8_t> getData() const { return _data; }

  void setLength(const int &length) { _length = length; }

  int getLength() const { return _length; }

  bool readData() {
    std::ifstream file(path(), std::ios::in | std::ios::binary);
    if (!file) {
      return false;
    }

    file.seekg(0, std::ios::end);
    _length = (int)file.tellg();
    file.seekg(0, std::ios::beg);

    _data.resize(_length);
    file.read((char *)_data.data(), _length);

    file.close();
    return true;
  }

  bool writeData() {
    std::ofstream file(path(), std::ios::out | std::ios::binary);
    if (!file) {
      return false;
    }

    file.write((const char *)_data.data(), _length);

    file.close();
    return true;
  }

  bool appendWriteData(std::vector<uint8_t> data) {
    std::ofstream file(path(),
                       std::ios::out | std::ios::binary | std::ios::app);
    if (!file) {
      return false;
    }

    _data.insert(_data.end(), data.begin(), data.end());
    _length = (int)_data.size();

    file.write((const char *)_data.data(), _length);

    file.close();
    return true;
  }
};

#endif  // BINFILE_HPP_
