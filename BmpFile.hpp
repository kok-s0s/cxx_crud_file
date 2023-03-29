#ifndef BMPFILE_HPP_
#define BMPFILE_HPP_

#include "UFile.hpp"
#include "bmp/BMP.h"

class BmpFile : public UFile {
 public:
  BmpFile() {}
  explicit BmpFile(const char* path) : UFile(path) {}
  explicit BmpFile(const std::string& path) : UFile(path) {}
  explicit BmpFile(const fs::path& path) : UFile(path) {}
  ~BmpFile() {}
};

#endif  // BMPFILE_HPP_
