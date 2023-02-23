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
      string tempStr = token;
      result.push_back(tempStr);
      token = strtok(NULL, thisSeparator);
    }
#endif

    return result;
  }

  /**
   * @brief 删除指定文件
   * @param dirPath 被搜索的文件夹路径
   * @param fileName 要删除的文件名
   * @param isRecursive
   * 是否递归，true为递归获取所有子文件夹内容，false为仅获取当前文件夹下的文件
   */
  static void deleteReferFile(std::string dirPath, std::string fileName,
                              bool isRecursive = true) {
    if (isRecursive) {
      for (auto const &dir_entry : fs::recursive_directory_iterator(dirPath)) {
        if (dir_entry.path().filename() == fileName) {
          remove(dir_entry.path());
        }
      }
    } else {
      for (auto const &dir_entry : fs::directory_iterator(dirPath)) {
        if (dir_entry.path().filename() == fileName) {
          remove(dir_entry.path());
        }
      }
    }
  }

  static void copyFile(const std::string &fromFile, const std::string &toFile,
                       const bool &coverFileIfExist) {
    fs::path file(toFile);
    fs::create_directories(file.parent_path());

    if (coverFileIfExist && fs::exists(toFile)) {
      fs::remove(toFile);
    }

    const auto copyOptions =
        fs::copy_options::update_existing | fs::copy_options::recursive;

    fs::copy(fromFile, toFile, copyOptions);
  }

  /**
   * @brief 复制文件夹中的文件
   */
  static bool copyDirectoryFiles(const std::string &fromDir,
                                 const std::string &toDir,
                                 const bool &coverFileIfExist) {
    if (!fs::exists(fromDir)) return false;

    fs::create_directories(toDir);

    for (auto const &dir_entry : fs::directory_iterator(fromDir)) {
      if (dir_entry.path().filename() == "." ||
          dir_entry.path().filename() == "..")
        continue;

      if (fs::is_directory(dir_entry.symlink_status())) {
        if (!copyDirectoryFiles(
                dir_entry.path().string(),
                (fs::path(toDir) / dir_entry.path().filename()).string(),
                coverFileIfExist)) {
          return false;
        }
      } else {
        if (coverFileIfExist &&
            fs::exists(
                (fs::path(toDir) / dir_entry.path().filename()).string())) {
          fs::remove((fs::path(toDir) / dir_entry.path().filename()).string());
        }

        const auto copyOptions =
            fs::copy_options::update_existing | fs::copy_options::recursive;

        fs::copy(dir_entry.path().string(),
                 (fs::path(toDir) / dir_entry.path().filename()).string(),
                 copyOptions);
      }
    }

    return true;
  }

  static std::fstream *getFileObj(const std::string &path) {
    std::fstream *file;
    if (fs::exists(path)) {
      file = new std::fstream;
      file->open(path, std::ios::in | std::ios::out | std::ios::binary);
    }
    return file;
  }

  /**
  ** @brief 从std::fstream中读取数据存储到另一个std::fstream
  ** @details 分段存储，减少内存申请
  ** @param file std::fstream的指针
  ** @param newFilePath 新存储的文件全路径
  ** @param startPos std::fstream的起始位置
  ** @param moveSize 需要存储的数据长度
  ** @return 成功返回true
  */
  static bool moveFromFileToFile(std::fstream *srcfile, std::fstream *desfile,
                                 const int &startPos, const int &moveSize) {
    int maxWriteLen = 1024 * 1024;
    int leftLen = moveSize;

    srcfile->seekg(startPos);

    srcfile->seekg(0, std::ios::end);
    int fileSize = (int)srcfile->tellg();
    srcfile->seekg(startPos, std::ios::beg);

    desfile->seekp(0, std::ios::end);

    std::vector<uint8_t> pos;
    while (leftLen > 0) {
      int writeLen = leftLen > maxWriteLen ? maxWriteLen : leftLen;
      leftLen = leftLen - writeLen;
      pos.resize(writeLen);

      if (fileSize < (int)srcfile->tellg() + writeLen) {
        return false;
      }

      srcfile->read((char *)pos.data(), writeLen * sizeof(char));

      desfile->write((const char *)pos.data(), writeLen * sizeof(char));
    }

    return true;
  }

  /**
  ** @brief 从std::fstream中读取数据存储到文件
  ** @details 分段存储，减少内存申请
  ** @param file std::fstream的指针
  ** @param newFilePath 新存储的文件全路径
  ** @param startPos std::fstream的起始位置
  ** @param moveSize 需要存储的数据长度
  ** @return 成功返回true
  */
  static bool moveFromFileDataToFile(std::fstream *file,
                                     const std::string &newFilePath,
                                     const int &startPos, const int &moveSize) {
    bool bRet = false;
    std::fstream tempFile;

    tempFile.open(newFilePath, std::ios::in | std::ios::out | std::ios::binary);

    if (!tempFile.is_open()) {
      return bRet;
    }

    bRet = moveFromFileToFile(file, &tempFile, startPos, moveSize);

    tempFile.close();

    return bRet;
  }

  /**
  ** @brief 将文件数据追加存储到std::fstream中，由外部决定是否要追加
  ** @details 分段存储，减少内存申请
  ** @param file std::fstream的指针
  ** @param filePath 文件全路径
  ** @return 成功返回true
  */
  static bool moveFromFileToFileData(std::fstream *file,
                                     const std::string &filePath) {
    std::fstream tempFile;

    tempFile.open(filePath, std::ios::in | std::ios::binary);

    if (!tempFile.is_open()) return false;

    int maxWriteLen = 1024 * 1024;
    tempFile.seekg(0, std::ios::end);
    int leftLen = (int)tempFile.tellg();
    tempFile.seekg(0, std::ios::beg);

    file->seekp(0, std::ios::end);

    std::vector<uint8_t> pos;
    while (leftLen > 0) {
      int writeLen = leftLen > maxWriteLen ? maxWriteLen : leftLen;
      leftLen = leftLen - writeLen;
      pos.resize(writeLen);

      tempFile.read((char *)pos.data(), writeLen * sizeof(char));

      file->write((const char *)pos.data(), writeLen * sizeof(char));
    }
    tempFile.close();

    return true;
  }

  // TODO tomorrow
  /**
   * @brief 遍历文件
   * @param dirPath       被搜索的文件夹路径
   * @param[out] fileInfo 搜索到的文件信息
   * @param fileName
   * 被搜索的文件名（带后缀），为空时搜索全部，仅当isDir为false时有效
   * @param isDir
   * 是否仅获取文件夹,true为获得所有文件夹路径，false为获取所有文件路径
   * @param isRecursive
   * 是否递归，true为递归获取所有子文件夹内容，false为仅获取当前文件夹下的文件
   * @param fileName
   * 被搜索的文件名（不带后缀），为空时搜索全部，仅当isDir为false且fileName为空时有效
   * @param baseName		   类型，仅当isDir为false且fileName为空时有效
   */
  // void searchFile(std::string dirPath, std::vector<QFileInfo> &fileInfo,
  //                 std::string fileName = "", bool isDir = false,
  //                 bool isRecursive = true, std::string baseName = "",
  //                 std::string suffix = "") {
  //   QDir dir(dirPath);
  //   dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

  //   for each (QFileInfo item in dir.entryInfoList()) {
  //     if (item.isFile()) {
  //       if (!isDir) {
  //         bool fileNameMatch =
  //             (!fileName.isEmpty()) &&
  //             (item.fileName().compare(fileName, Qt::CaseInsensitive) == 0);
  //         bool baseNameOrSuffixMatch =
  //             fileName.isEmpty() &&
  //             (suffix.isEmpty() || item.completeSuffix().compare(
  //                                      suffix, Qt::CaseInsensitive) == 0) &&
  //             (fileName.isEmpty() || item.completeBaseName().compare(
  //                                        fileName, Qt::CaseInsensitive) ==
  //                                        0);
  //         if (fileNameMatch || baseNameOrSuffixMatch) {
  //           fileInfo.push_back(item);
  //         }
  //       }
  //     } else {
  //       if (isDir) {
  //         fileInfo.push_back(item);
  //       }
  //       if (isRecursive) {
  //         searchFile(item.absoluteFilePath(), fileInfo, fileName, isDir,
  //                    isRecursive, baseName, suffix);
  //       }
  //     }
  //   }
  // }
};

#endif  // UFILE_HPP_
