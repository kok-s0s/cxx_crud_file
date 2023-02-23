#ifndef DATFILE_HPP_
#define DATFILE_HPP_

#include "UFile.hpp"

#if defined(_WIN32)
#pragma warning(disable : 4996)
#endif

class DatFile : public UFile {
 private:
  std::vector<uint8_t> _data;

 public:
  DatFile() {}
  DatFile(const char *path) : UFile(path) {}
  DatFile(const std::string &path) : UFile(path) {}
  DatFile(const fs::path &path) : UFile(path) {}
  ~DatFile() {}

  std::vector<uint8_t> getData() { return _data; }

  bool readData() {
    FILE *fid = fopen(getPath().c_str(), "rb");

    if (fid == NULL) return false;

    fseek(fid, 0, SEEK_END);
    long lSize = ftell(fid);
    rewind(fid);

    int num = lSize / sizeof(uint8_t);
    char *pos = (char *)malloc(sizeof(uint8_t) * num);

    if (pos == NULL) return false;

    size_t temp = fread(pos, sizeof(uint8_t), num, fid);

    for (int i = 0; i < num; ++i) _data.push_back(pos[i]);

    free(pos);

    fclose(fid);

    return true;
  }

  bool writeData() {
    FILE *fid = fopen(getPath().c_str(), "wb");

    if (fid == NULL) return false;

    fwrite(&_data[0], sizeof(uint8_t), _data.size(), fid);

    fclose(fid);

    return true;
  }

  static bool readDatFile(const std::string &datFilePath, uint8_t *varibale,
                          const int &num) {
    FILE *fid = fopen(datFilePath.c_str(), "rb");

    if (fid == NULL) return false;

    fseek(fid, 0, SEEK_END);
    long lSize = ftell(fid);
    rewind(fid);

    if (lSize / sizeof(uint8_t) < num) return false;

    size_t temp = fread(varibale, sizeof(uint8_t), num, fid);

    fclose(fid);

    return true;
  }

  static bool writeDataToDatFile(const std::string &datFilePath, uint8_t *data,
                                 const int &size) {
    FILE *fid = fopen(datFilePath.c_str(), "wb");

    if (fid == NULL) return false;

    fwrite(data, sizeof(uint8_t), size, fid);

    fclose(fid);

    return true;
  }

  static bool appendWriteDataToDatFile(const std::string &datFilePath,
                                       uint8_t *data, const size_t &size) {
    FILE *fid = fopen(datFilePath.c_str(), "ab");

    if (fid == NULL) return false;

    fwrite(data, sizeof(uint8_t), size, fid);

    fclose(fid);

    return true;
  }

  static bool saveDatFileExt(const std::string &fileName, uint8_t *extData,
                             const int &extDataSize, uint8_t *data,
                             const int &dataSize) {
    if (!fs::exists(fs::path(fileName).parent_path()))
      fs::create_directory(fs::path(fileName).parent_path());

    FILE *fid = fopen(fileName.c_str(), "wb");

    if (fid == NULL) return false;

    if (extData != nullptr && extDataSize != 0) {
      fwrite(extData, sizeof(uint8_t), extDataSize, fid);
    }

    fwrite(data, sizeof(uint8_t), dataSize, fid);

    fclose(fid);

    return true;
  }

  static bool saveOutputData(int *extData, const int &extDataCount,
                             const std::string &absoluteFilePath, uint8_t *data,
                             const int &dataSize) {
    const int extDataSize = extDataCount * sizeof(int);
    return saveDatFileExt(absoluteFilePath, (uint8_t *)extData, extDataSize,
                          data, dataSize);
  }
};

#endif  // DATFILE_HPP_
