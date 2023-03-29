#ifndef BINFILE_HPP_
#define BINFILE_HPP_

#include <fstream>

#include "UFile.hpp"

class BinFile : public UFile {
 private:
  std::vector<uint8_t> _data;
  int _length = 0;

 public:
  BinFile() {}
  explicit BinFile(const char *path) : UFile(path) {}
  explicit BinFile(const std::string &path) : UFile(path) {}
  explicit BinFile(const fs::path &path) : UFile(path) {}
  ~BinFile() {}

  void setData(const std::vector<uint8_t> &data) { _data = data; }

  std::vector<uint8_t> getData() { return _data; }

  void setLength(const int &length) { _length = length; }

  int getLength() { return _length; }

  bool readData() {
    std::ifstream file;

    file.open(getPath(), std::ios::in | std::ios::binary);

    if (!file.is_open()) return false;

    file.seekg(0, std::ios::end);
    _length = (int)file.tellg();
    file.seekg(0, std::ios::beg);

    _data.resize(_length);
    file.read((char *)_data.data(), _length * sizeof(char));

    file.close();

    return true;
  }

  bool writeData() {
    std::ofstream out;
    out.open(getPath(), std::ios::out | std::ios::binary);

    if (!out.is_open()) return false;

    out.write((const char *)_data.data(), _length * sizeof(char));

    out.close();

    return true;
  }

  bool appendWriteData(std::vector<uint8_t> data) {
    std::ofstream out;
    out.open(getPath(), std::ios::out | std::ios::binary);

    if (!out.is_open()) return false;

    _data.insert(_data.end(), data.begin(), data.end());
    _length = _data.size();

    out.write((const char *)_data.data(), _length * sizeof(char));

    out.close();

    return true;
  }
};

#endif  // BINFILE_HPP_
