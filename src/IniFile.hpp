#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include "UFile.hpp"
#include "ini/SimpleIni.h"

class IniFile : public UFile {
 private:
  CSimpleIniA _ini;

 public:
  explicit IniFile(const std::string &path) : UFile(path) {}
  explicit IniFile(const fs::path &path) : UFile(path) {}
  ~IniFile() {}

  bool setup() {
    _ini.SetUnicode();
    SI_Error rc = _ini.LoadFile(path().c_str());
    if (rc < 0) return false;
    return true;
  }

  void getFromIni(const std::string &section, const std::string &key,
                  std::string &param, const char *defaultVal) {
    param = _ini.GetValue(section.c_str(), key.c_str(), defaultVal);
  }

  template <typename T>
  void getFromIni(const std::string &section, const std::string &key, T &param,
                  const T defaultVal) {
    std::string paramType = typeid(T).name();
    std::string tempParam;
    tempParam = _ini.GetValue(section.c_str(), key.c_str(),
                              std::to_string(defaultVal).c_str());

    if (paramType[0] == 'i')
      param = static_cast<T>(stoi(tempParam));
    else if (paramType[0] == 'f')
      param = static_cast<T>(stof(tempParam));
    else if (paramType[0] == 'd')
      param = static_cast<T>(stod(tempParam));
    else if (paramType[0] == 'b') {
      if (tempParam == "false" || tempParam == "0") {
        param = false;
      } else if (tempParam == "true" || tempParam == "1") {
        param = true;
      }
    }
  }

  template <typename T>
  void getFromIni(const std::string &section, const std::string &key, T *param,
                  const T *defaultVal, const int &size) {
    int index = 0;

    std::string paramType = typeid(T).name();

    if (_ini.GetValue(section.c_str(), key.c_str()) == nullptr)
      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    else {
      std::string tempParamArrayStr =
          _ini.GetValue(section.c_str(), key.c_str());
      std::vector<std::string> tempParamArray =
          split(tempParamArrayStr, " ,\t\n");

      if (paramType[0] == 'i')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = static_cast<T>(stoi(tempParamArray[i]));
      else if (paramType[0] == 'f')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = static_cast<T>(stof(tempParamArray[i]));
      else if (paramType[0] == 'd')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = static_cast<T>(stod(tempParamArray[i]));

      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    }
  }

  void setToIni(const std::string &section, const std::string &key,
                const char *fromValue) {
    _ini.SetValue(section.c_str(), key.c_str(), fromValue);
  }

  template <typename T>
  void setToIni(const std::string &section, const std::string &key,
                const T fromValue) {
    std::string valueType = typeid(T).name();
    std::string toValue;

    if (valueType[0] == 'i')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'f')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'd')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'b') {
      if ((bool)fromValue == false) {
        toValue = "false";
      } else if ((bool)fromValue == true) {
        toValue = "true";
      }
    }

    _ini.SetValue(section.c_str(), key.c_str(), toValue.c_str());
  }

  template <typename T>
  void setToIni(const std::string &section, const std::string &key,
                const T *fromValueArr, const int &size) {
    if (size <= 0) return;

    std::string valueType = typeid(T).name();
    std::string toValueArr;

    if (valueType[0] == 'i')
      for (int i = 0; i < size; ++i) {
        toValueArr += std::to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }
    else if (valueType[0] == 'f')
      for (int i = 0; i < size; ++i) {
        toValueArr += std::to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }
    else if (valueType[0] == 'd')
      for (int i = 0; i < size; ++i) {
        toValueArr += std::to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }

    _ini.SetValue(section.c_str(), key.c_str(), toValueArr.c_str());
  }

  void save() {
    std::string output;
    _ini.Save(output);
    _ini.SaveFile(path().c_str());
  }
};

#endif  // INIFILE_HPP_
