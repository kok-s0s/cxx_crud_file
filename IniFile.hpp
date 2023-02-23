#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include <fstream>

#include "UFile.hpp"
#include "ini/SimpleIni.h"

class IniFile : public UFile {
 private:
  CSimpleIniA _ini;

 public:
  IniFile() {}
  IniFile(const char *path) : UFile(path) {}
  IniFile(const std::string &path) : UFile(path) {}
  IniFile(const fs::path &path) : UFile(path) {}
  ~IniFile() {}

  bool iniSetup() {
    _ini.SetUnicode();

    const char *path = (char *)getPath().c_str();

    SI_Error rc = _ini.LoadFile(path);
    if (rc < 0) return false;

    return true;
  }

  void getFromIni(const char *section, const char *key, std::string &param,
                  const char *defaultVal) {
    param = _ini.GetValue(section, key, defaultVal);
  }

  template <typename T>
  void getFromIni(const char *section, const char *key, T &param,
                  T defaultVal) {
    const char *name = typeid(T).name();
    std::string paramType = name;
    std::string tempParam;
    tempParam = _ini.GetValue(section, key, std::to_string(defaultVal).c_str());

    if (paramType[0] == 'i')
      param = stoi(tempParam);
    else if (paramType[0] == 'f')
      param = stof(tempParam);
    else if (paramType[0] == 'd')
      param = stod(tempParam);
    else if (paramType[0] == 'b')
      if (tempParam == "false" || tempParam == "0")
        param = false;
      else if (tempParam == "true" || tempParam == "1")
        param = true;
  }

  template <typename T>
  void getFromIni(const char *section, const char *key, T *param, T *defaultVal,
                  const int &size) {
    int index = 0;

    const char *name = typeid(T).name();
    std::string paramType = name;

    if (_ini.GetValue(section, key) == nullptr)
      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    else {
      std::string tempParamArrayStr = _ini.GetValue(section, key);
      std::vector<std::string> tempParamArray =
          split(tempParamArrayStr, " ,\t\n");

      if (paramType[0] == 'i')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = stoi(tempParamArray[i]);
      else if (paramType[0] == 'f')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = stof(tempParamArray[i]);
      else if (paramType[0] == 'd')
        for (int i = 0; i < tempParamArray.size(); ++i)
          param[index++] = stod(tempParamArray[i]);

      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    }
  }

  void setToIni(const char *section, const char *key, const char *fromValue) {
    std::string toValue = fromValue;
    const char *toValueC = (char *)toValue.c_str();
    _ini.SetValue(section, key, toValueC);
  }

  template <typename T>
  void setToIni(const char *section, const char *key, T fromValue) {
    const char *name = typeid(T).name();
    std::string valueType = name;
    std::string toValue;

    if (valueType[0] == 'i')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'f')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'd')
      toValue = std::to_string(fromValue);
    else if (valueType[0] == 'b')
      if ((bool)fromValue == false)
        toValue = "false";
      else if ((bool)fromValue == true)
        toValue = "true";

    const char *toValueC = (char *)toValue.c_str();

    _ini.SetValue(section, key, toValueC);
  }

  template <typename T>
  void setToIni(const char *section, const char *key, T *fromValueArr,
                const int &size) {
    if (size <= 0) return;

    const char *name = typeid(T).name();
    std::string valueType = name;
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

    const char *toValueC = (char *)toValueArr.c_str();

    _ini.SetValue(section, key, toValueC);
  }

  void save() {
    std::string output;
    _ini.Save(output);
    const char *path = (char *)getPath().c_str();
    _ini.SaveFile(path);
  }
};

#endif  // INIFILE_HPP_
