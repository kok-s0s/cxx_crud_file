#ifndef FILETOOLS_HPP_
#define FILETOOLS_HPP_

#if defined(_MSC_VER)
#include <direct.h>
#define GetCurrentDir _getcwd
#elif defined(__GNUC__)
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "bmp/BMP.h"
#include "ini/SimpleIni.h"
#include "json/json.hpp"

using std::fstream;
using std::ios;
using std::string;
using std::to_string;
using std::vector;

using json = nlohmann::json;

struct TxtFile {
  string path;
  string data = "";
};

struct IniFile {
  string path;
  CSimpleIniA ini;
};

struct JsonFile {
  string path;
  json data;
};

struct DatFile {
  string path;
  vector<char> data;
};

struct BmpFile {
  string path;
};

class FileTools {
 private:
  vector<string> split(const string &data, const string &separator) {
    vector<string> result;
    if (data == "") return result;

    char *thisStr = new char[data.length() + 1];
    char *thisSeparator = new char[separator.length() + 1];

#if defined(_MSC_VER)
    strcpy_s(thisStr, data.length() + 1, data.c_str());
    strcpy_s(thisSeparator, separator.length() + 1, separator.c_str());

    char *next_token = NULL;
    char *token = strtok_s(thisStr, thisSeparator, &next_token);
    while (token) {
      string tempStr = token;
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

 public:
#pragma region path

  void createDirectory(const string &path) {
#if defined(_MSC_VER)
    _mkdir(path.c_str());
#elif defined(__GNUC__)
    mkdir(path.c_str(), 0755);
#endif
  }

  bool deleteDirectory(string path) {
#if defined(_MSC_VER)
    struct _finddata_t fb;

    if (path.at(path.length() - 1) != '\\' || path.at(path.length() - 1) != '/')
      path.append("\\");

    string findPath = path + "*";
    intptr_t handle;
    handle = _findfirst(findPath.c_str(), &fb);

    if (handle != -1L) {
      string pathTemp;
      do {
        if (strcmp(fb.name, "..") != 0 && strcmp(fb.name, ".") != 0) {
          pathTemp.clear();
          pathTemp = path + std::string(fb.name);

          if (fb.attrib == _A_SUBDIR) {
            deleteDirectory(pathTemp.c_str());
          }

          else {
            remove(pathTemp.c_str());
          }
        }
      } while (0 == _findnext(handle, &fb));
      _findclose(handle);
    }

    return _rmdir(path.c_str()) == 0 ? true : false;

#elif defined(__GNUC__)
    if (path.at(path.length() - 1) != '\\' || path.at(path.length() - 1) != '/')
      path.append("/");

    DIR *d = opendir(path.c_str());

    if (d != NULL) {
      struct dirent *dt = NULL;

      while (dt = readdir(d)) {
        if (strcmp(dt->d_name, "..") != 0 && strcmp(dt->d_name, ".") != 0) {
          struct stat st;
          string fileName;
          fileName = path + std::string(dt->d_name);
          stat(fileName.c_str(), &st);

          if (S_ISDIR(st.st_mode)) {
            deleteDirectory(fileName);
          } else {
            remove(fileName.c_str());
          }
        }
      }
      closedir(d);
    }

    return rmdir(path.c_str()) == 0 ? true : false;

#endif
  }

  string getCurrentDirectory() {
    char buff[250];
    char *temp = GetCurrentDir(buff, 250);
    string current_working_directory(buff);
    return current_working_directory;
  }

  string mergePathArgs(string arg) { return arg.append("/"); }

  string mergePathArgs(const char *arg) {
    string temp = arg;
    return temp.append("/");
  }

  template <typename... T>
  string mergePathArgs(const string &arg, T &...args) {
    string path;
    path = mergePathArgs(arg);
    path += mergePathArgs(args...);
    if (path[path.size() - 1] == '/') path.pop_back();
    return path;
  }

  template <typename... T>
  string mergePathArgs(const char *arg, T &...args) {
    string path;
    path = mergePathArgs(arg);
    path += mergePathArgs(args...);
    if (path[path.size() - 1] == '/') path.pop_back();
    return path;
  }

  bool pathExistFlag(const string &path) {
    struct stat buffer;
    return (stat(path.c_str(), &buffer) == 0);
  }

#pragma endregion

#pragma region txt

  bool readTxtFileLine(TxtFile &txtFile) {
    string ln;
    fstream file;

    file.open(txtFile.path, ios::in);

    if (file.is_open()) {
      while (getline(file, ln)) txtFile.data += (ln + "\n");

      file.close();

      return true;
    } else
      return false;
  }

  bool writeDataToTxtFile(TxtFile &txtFile, string data) {
    fstream file;

    file.open(txtFile.path, ios::out);

    if (file.is_open()) {
      file << data;
      txtFile.data = data;

      file.close();

      return true;
    } else
      return false;
  }

#pragma endregion

#pragma region ini

  bool iniSetup(IniFile &iniFile) {
    iniFile.ini.SetUnicode();

    const char *path = (char *)iniFile.path.c_str();

    SI_Error rc = iniFile.ini.LoadFile(path);
    if (rc < 0) return false;

    return true;
  }

  void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  string &param, const char *defaultVal) {
    param = iniFile.ini.GetValue(section, key, defaultVal);
  }

  template <typename T>
  void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T &param, T defaultVal) {
    const char *name = typeid(T).name();
    string paramType = name;
    string tempParam;
    tempParam =
        iniFile.ini.GetValue(section, key, to_string(defaultVal).c_str());

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
  void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T *param, T *defaultVal, const int &size) {
    int index = 0;

    const char *name = typeid(T).name();
    string paramType = name;

    if (iniFile.ini.GetValue(section, key) == nullptr)
      while (index <= size - 1) {
        param[index] = defaultVal[index];
        index++;
      }
    else {
      string tempParamArrayStr = iniFile.ini.GetValue(section, key);
      vector<string> tempParamArray = split(tempParamArrayStr, " ,\t\n");

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

  void setToIni(IniFile &iniFile, const char *section, const char *key,
                const char *fromValue) {
    string toValue = fromValue;
    const char *toValueC = (char *)toValue.c_str();
    iniFile.ini.SetValue(section, key, toValueC);
  }

  template <typename T>
  void setToIni(IniFile &iniFile, const char *section, const char *key,
                T fromValue) {
    const char *name = typeid(T).name();
    string valueType = name;
    string toValue;

    if (valueType[0] == 'i')
      toValue = to_string(fromValue);
    else if (valueType[0] == 'f')
      toValue = to_string(fromValue);
    else if (valueType[0] == 'd')
      toValue = to_string(fromValue);
    else if (valueType[0] == 'b')
      if (fromValue == false)
        toValue = "false";
      else if (fromValue == true)
        toValue = "true";

    const char *toValueC = (char *)toValue.c_str();

    iniFile.ini.SetValue(section, key, toValueC);
  }

  template <typename T>
  void setToIni(IniFile &iniFile, const char *section, const char *key,
                T *fromValueArr, const int &size) {
    if (size <= 0) return;

    const char *name = typeid(T).name();
    string valueType = name;
    string toValueArr;

    if (valueType[0] == 'i')
      for (int i = 0; i < size; ++i) {
        toValueArr += to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }
    else if (valueType[0] == 'f')
      for (int i = 0; i < size; ++i) {
        toValueArr += to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }
    else if (valueType[0] == 'd')
      for (int i = 0; i < size; ++i) {
        toValueArr += to_string(fromValueArr[i]);
        if (i != size - 1) toValueArr += ", ";
      }

    const char *toValueC = (char *)toValueArr.c_str();

    iniFile.ini.SetValue(section, key, toValueC);
  }

#pragma endregion

#pragma region json

  bool readDataFromJsonFile(JsonFile &jsonFile) {
    fstream file;

    file.open(jsonFile.path, ios::in);

    if (file.is_open()) {
      file >> jsonFile.data;

      file.close();

      return true;
    } else
      return false;
  }

  void getFromJsonData(const JsonFile &jsonFile, const string &key,
                       string &param, string defaultVal) {
    json temp = jsonFile.data;
    vector<string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1]))
      param = temp.at(keyArr[keyArr.size() - 1]);
    else
      param = defaultVal;
  }

  template <typename T>
  void getFromJsonData(const JsonFile &jsonFile, const string &key, T &param,
                       T defaultVal) {
    json temp = jsonFile.data;
    vector<string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    if (temp.contains(keyArr[keyArr.size() - 1]))
      param = temp.at(keyArr[keyArr.size() - 1]);
    else
      param = defaultVal;
  }

  void getFromJsonData(const JsonFile &jsonFile, const string &key,
                       string *param, string *defaultVal, const int &size) {
    json temp = jsonFile.data;
    vector<string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    int index = 0;

    if (temp.contains(keyArr[keyArr.size() - 1])) {
      const json thisKeyArrValue = temp.at(keyArr[keyArr.size() - 1]);

      for (int i = 0; i < thisKeyArrValue.size(); ++i)
        param[index++] = thisKeyArrValue[index];
    }

    if (index < size)
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
  }

  template <typename T>
  void getFromJsonData(const JsonFile &jsonFile, const string &key, T *param,
                       T *defaultVal, const int &size) {
    json temp = jsonFile.data;
    vector<string> keyArr = split(key, ".");

    for (int i = 0; i < keyArr.size() - 1; ++i)
      if (temp.contains(keyArr[i])) temp = temp.at(keyArr[i]);

    int index = 0;

    if (temp.contains(keyArr[keyArr.size() - 1])) {
      const json thisKeyArrValue = temp.at(keyArr[keyArr.size() - 1]);

      for (int i = 0; i < thisKeyArrValue.size(); ++i)
        param[index++] = thisKeyArrValue[index];
    }

    if (index < size)
      for (int i = index; i < size; ++i) param[i] = defaultVal[i];
  }

#pragma endregion

#pragma region dat

  bool readDatFile(DatFile &datFile) {
    FILE *fid = fopen(datFile.path.c_str(), "rb");

    if (fid == NULL) return false;

    fseek(fid, 0, SEEK_END);
    long lSize = ftell(fid);
    rewind(fid);

    int num = lSize / sizeof(char);
    char *pos = (char *)malloc(sizeof(char) * num);

    if (pos == NULL) return false;

    size_t temp = fread(pos, sizeof(char), num, fid);

    for (int i = 0; i < num; ++i) datFile.data.push_back(pos[i]);

    free(pos);
    fclose(fid);

    return true;
  }

  bool readDatFile(DatFile &datFile, char *varibale, const int &num) {
    FILE *fid = fopen(datFile.path.c_str(), "rb");

    if (fid == NULL) return false;

    fseek(fid, 0, SEEK_END);
    long lSize = ftell(fid);
    rewind(fid);

    if (lSize / sizeof(char) != num) return false;

    size_t temp = fread(varibale, sizeof(char), num, fid);

    fclose(fid);

    return true;
  }

  bool writeDataToDatFile(const DatFile &datFile) {
    FILE *fid = fopen(datFile.path.c_str(), "wb");

    if (fid == NULL) return false;

    for (int i = 0; i < datFile.data.size(); ++i)
      fwrite(&datFile.data[i], sizeof(char), 1, fid);

    fclose(fid);

    return true;
  }

#pragma endregion

#pragma region bmp

  // TODO obligate

#pragma endregion
};

#endif  // FILETOOLS_HPP_