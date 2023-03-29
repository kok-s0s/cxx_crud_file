#ifndef INIFILE_HPP_
#define INIFILE_HPP_

#include "UFile.hpp"
#include "ini/SimpleIni.h"

class IniFile : public UFile {
 private:
  CSimpleIniA _ini;

 public:
  IniFile() {}
  explicit IniFile(const char *path) : UFile(path) {}
  explicit IniFile(const std::string &path) : UFile(path) {}
  explicit IniFile(const fs::path &path) : UFile(path) {}
  ~IniFile() {}

  bool iniSetup() {
    _ini.SetUnicode();

    std::string path = getPath();

    SI_Error rc = _ini.LoadFile(path.c_str());
    if (rc < 0) return false;

    return true;
  }

  void getFromIni(const char *section, const char *key, std::string &param,
                  const char *defaultVal) {
    param = _ini.GetValue(section, key, defaultVal);
  }

  void getFromIni(const std::string &section, const std::string &key,
                  std::string &param, const char *defaultVal) {
    getFromIni(section.c_str(), key.c_str(), param, defaultVal);
  }

  template <typename T>
  void getFromIni(const char *section, const char *key, T &param,
                  const T defaultVal) {
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
  void getFromIni(const std::string &section, const std::string &key, T &param,
                  const T defaultVal) {
    getFromIni(section.c_str(), key.c_str(), param, defaultVal);
  }

  template <typename T>
  void getFromIni(const char *section, const char *key, T *param,
                  const T *defaultVal, const int &size) {
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

  template <typename T>
  void getFromIni(const std::string &section, const std::string &key, T *param,
                  const T *defaultVal, const int &size) {
    getFromIni(section.c_str(), key.c_str(), param, defaultVal, size);
  }

  void setToIni(const char *section, const char *key, const char *fromValue) {
    std::string toValue = fromValue;
    const char *toValueC = (char *)toValue.c_str();
    _ini.SetValue(section, key, toValueC);
  }

  void setToIni(const std::string &section, const std::string &key,
                const char *fromValue) {
    setToIni(section.c_str(), key.c_str(), fromValue);
  }

  template <typename T>
  void setToIni(const char *section, const char *key, const T fromValue) {
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
  void setToIni(const std::string &section, const std::string &key,
                const T fromValue) {
    setToIni(section.c_str(), key.c_str(), fromValue);
  }

  template <typename T>
  void setToIni(const char *section, const char *key, const T *fromValueArr,
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

  template <typename T>
  void setToIni(const std::string &section, const std::string &key,
                const T *fromValueArr, const int &size) {
    setToIni(section.c_str(), key.c_str(), fromValueArr, size);
  }

  void save() {
    std::string output;
    _ini.Save(output);
    _ini.SaveFile(getPath().c_str());
  }
};

#endif  // INIFILE_HPP_
