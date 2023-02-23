#ifndef IMGFILE_HPP_
#define IMGFILE_HPP_

#include <fstream>

#include "UFile.hpp"

class ImgFile : public UFile {
 private:
  uint8_t* _data;
  int _length;

 public:
  ImgFile(const std::string& path) : UFile(path) {}
  ImgFile(const fs::path& path) : UFile(path) {}
  ~ImgFile() {}

  void setData(uint8_t* data) { _data = data; }

  uint8_t* getData() { return _data; }

  void setLength(const int& length) { _length = length; }

  int getLength() { return _length; }

  bool readData() {
    std::ifstream file;

    file.open(getPath(), std::ios::in | std::ios::binary);

    if (!file.is_open()) return false;

    file.seekg(0, std::ios::end);
    _length = (int)file.tellg();
    file.seekg(0, std::ios::beg);

    _data = new uint8_t[_length];
    file.read((char*)_data, _length * sizeof(char));

    file.close();

    return true;
  }

  bool writeData() {
    std::ofstream out;
    out.open(getPath(), std::ios::out | std::ios::binary);

    if (!out.is_open()) return false;

    out.write((const char*)_data, _length * sizeof(char));

    out.close();
    delete[] _data;
    return true;
  }
};

#endif  // IMGFILE_HPP_
