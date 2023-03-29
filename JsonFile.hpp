#ifndef JSONFILE_HPP_
#define JSONFILE_HPP_

#include "UFile.hpp"
#include "json/json.hpp"

using json = nlohmann::json;

class JsonFile : public UFile {
 public:
  json _data;

  JsonFile() {}
  explicit JsonFile(const char *path) : UFile(path) {}
  explicit JsonFile(const std::string &path) : UFile(path) {}
  explicit JsonFile(const fs::path &path) : UFile(path) {}
  ~JsonFile() {}

  bool jsonSetup() {
    std::fstream file;

    file.open(getPath(), std::ios::in);

    if (file.is_open()) {
      file >> _data;

      file.close();

      return true;
    } else
      return false;
  }

  void getFromJson(const std::string &key, std::string &param,
                   const std::string &defaultVal) {
    if (key == "") {
      param = defaultVal;
      return;
    }

    json temp = _data;
    std::vector<std::string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1]))
      param = temp.at(keyArr[keyArr.size() - 1]);
    else
      param = defaultVal;
  }

  template <typename T>
  void getFromJson(const std::string &key, T &param, T defaultVal) {
    if (key == "") {
      param = defaultVal;
      return;
    }

    json temp = _data;
    std::vector<std::string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1]))
      param = temp.at(keyArr[keyArr.size() - 1]);
    else
      param = defaultVal;
  }

  void getFromJson(const std::string &key, std::string *param,
                   const std::string *defaultVal, const int &size) {
    int index = 0;

    if (key == "") {
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
      return;
    }

    json temp = _data;
    std::vector<std::string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1])) {
      const json thisKeyArrValue = temp.at(keyArr[keyArr.size() - 1]);

      for (int i = 0; i < thisKeyArrValue.size(); ++i)
        param[index++] = thisKeyArrValue[index];
    }

    if (index < size)
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
  }

  template <typename T>
  void getFromJson(const std::string &key, T *param, const T *defaultVal,
                   const int &size) {
    int index = 0;

    if (key == "") {
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
      return;
    }

    json temp = _data;
    std::vector<std::string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1])) {
      const json thisKeyArrValue = temp.at(keyArr[keyArr.size() - 1]);

      for (int i = 0; i < thisKeyArrValue.size(); ++i)
        param[index++] = thisKeyArrValue[index];
    }

    if (index < size)
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
  }

  void save() {
    std::ofstream file(getPath());
    file << _data;
    file.flush();
  }
};

#endif  // JSONFILE_HPP_
