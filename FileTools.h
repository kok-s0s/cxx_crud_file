#include "SimpleIni.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct TxtFile {
  std::string path;
  std::string data = "";
};

struct IniFile {
  std::string path;
};

class FileTools {
private:
  std::vector<std::string> split(const std::string &data,
                                 const std::string &separator) {
    std::vector<std::string> result;
    if (data == "") {
      return result;
    }

    char *thisStr = new char[data.length() + 1];
    strcpy_s(thisStr, data.length() + 1, data.c_str());

    char *thisSeparator = new char[separator.length() + 1];
    strcpy_s(thisSeparator, separator.length() + 1, separator.c_str());

    char *next_token = NULL;
    char *token = strtok_s(thisStr, thisSeparator, &next_token);
    while (token) {
      std::string tempStr = token;
      result.push_back(tempStr);
      token = strtok_s(NULL, thisSeparator, &next_token);
    }

    return result;
  }

public:
  bool readTxtFileLine(TxtFile &txtFile) {
    std::string ln;
    std::fstream file;

    file.open(txtFile.path, std::ios::in);

    if (file.is_open()) {
      while (std::getline(file, ln)) {
        txtFile.data += (ln + "\n");
      }
      file.close();

      return true;
    } else
      return false;
  };

  bool writeDataToTxtFile(TxtFile &txtFile, std::string data) {
    std::fstream file;

    file.open(txtFile.path, std::ios::out);

    if (file.is_open()) {
      file << data;
      txtFile.data = data;

      file.close();

      return true;
    } else
      return false;
  };

  bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  std::string &param, const char *defaultVal) {
    CSimpleIniA ini;
    ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = ini.LoadFile(path);
    if (rc < 0) {
      return false;
    }

    param = ini.GetValue(section, key, defaultVal);

    return true;
  };

  template <typename T>
  bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T &param, T defaultVal) {
    CSimpleIniA ini;
    ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = ini.LoadFile(path);
    if (rc < 0) {
      return false;
    }

    const char *name = typeid(T).name();
    std::string paramType = name;
    std::string tempParam;
    tempParam = ini.GetValue(section, key, std::to_string(defaultVal).c_str());

    if (paramType == "int") {
      param = std::stoi(tempParam);
    } else if (paramType == "float") {
      param = std::stof(tempParam);
    } else if (paramType == "double") {
      param = std::stod(tempParam);
    } else if (paramType == "bool") {
      if (tempParam == "false" || tempParam == "0") {
        param = false;
      } else if (tempParam == "true" || tempParam == "1") {
        param = true;
      }
    }

    return true;
  };

  template <typename T>
  bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T *param, T *defaultVal, const int &size) {
    CSimpleIniA ini;
    ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = ini.LoadFile(path);
    if (rc < 0) {
      return false;
    }

    int index = 0;

    const char *name = typeid(T).name();
    std::string paramType = name;
    if (ini.GetValue(section, key) == nullptr) {
      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    } else {
      std::string tempParamArrayStr = ini.GetValue(section, key);
      std::vector<std::string> tempParamArray =
          split(tempParamArrayStr, " ,\t\n");

      if (paramType == "int") {
        for (int i = 0; i < tempParamArray.size(); ++i) {
          param[index++] = std::stoi(tempParamArray[i]);
        }
      } else if (paramType == "float") {
        for (int i = 0; i < tempParamArray.size(); ++i) {
          param[index++] = std::stof(tempParamArray[i]);
        }
      } else if (paramType == "double") {
        for (int i = 0; i < tempParamArray.size(); ++i) {
          param[index++] = std::stod(tempParamArray[i]);
        }
      }

      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    }

    return true;
  };

  bool setToIni(const IniFile &iniFile, const char *section, const char *key,
                const char *fromValue) {
    CSimpleIniA ini;
    ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = ini.LoadFile(path);
    if (rc < 0) {
      return false;
    }

    std::string toValue = fromValue;

    const char *toValueC = (char *)toValue.c_str();

    rc = ini.SetValue(section, key, toValueC);
    if (rc < 0) {
      return false;
    }

    std::string output;
    ini.Save(output);
    if (rc < 0) {
      return false;
    }

    rc = ini.SaveFile(path);
    if (rc < 0) {
      return false;
    }

    return true;
  };

  template <typename T>
  bool setToIni(const IniFile &iniFile, const char *section, const char *key,
                T fromValue) {
    CSimpleIniA ini;
    ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = ini.LoadFile(path);
    if (rc < 0) {
      return false;
    }

    const char *name = typeid(T).name();
    std::string valueType = name;
    std::string toValue;

    if (valueType == "int") {
      toValue = std::to_string(fromValue);
    } else if (valueType == "float") {
      toValue = std::to_string(fromValue);
    } else if (valueType == "double") {
      toValue = std::to_string(fromValue);
    } else if (valueType == "bool") {
      if (fromValue == false) {
        toValue = "false";
      } else if (fromValue == true) {
        toValue = "true";
      }
    }

    const char *toValueC = (char *)toValue.c_str();

    rc = ini.SetValue(section, key, toValueC);
    if (rc < 0) {
      return false;
    }

    std::string output;
    ini.Save(output);
    if (rc < 0) {
      return false;
    }

    rc = ini.SaveFile(path);
    if (rc < 0) {
      return false;
    }

    return true;
  };
};
