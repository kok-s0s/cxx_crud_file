# cxx_crud_file_windows

## Development environment

**Available C++ Compilers**

- `Visual Studio 生成工具 2022 Release - x86_amd64`

**VSCode extensions**

- `C/C++`
- `CMake`
- `CMake Tools`
- `clang-format`
- `Hex Editor`

## Test-Driven Development (TDD)

[GoogleTest](http://google.github.io/googletest/quickstart-cmake.html)

## Function

### path

```cxx
string get_current_directory();

string mergePathArgs(string arg);

string mergePathArgs(const char *arg);

template <typename... T> string mergePathArgs(string &arg, T &... args);

template <typename... T> string mergePathArgs(const char *arg, T &... args);

bool pathExistFlag(const string &path);
```

### txt

```cxx
struct TxtFile {
  string path;
  string data = "";
};

bool readTxtFileLine(TxtFile &txtFile);

bool writeDataToTxtFile(TxtFile &txtFile, string data);
```

### ini

Based On `simpleini` --- [Github](https://github.com/brofield/simpleini)

```cxx
struct IniFile {
  string path;
  CSimpleIniA ini;
};

bool iniSetup(IniFile &iniFile);

void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                string &param, const char *defaultVal);

template <typename T>
void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                T &param, T defaultVal);

template <typename T>
void getFromIni(const IniFile &iniFile, const char *section, const char *key,
                T *param, T *defaultVal, const int &size);

void setToIni(IniFile &iniFile, const char *section, const char *key,
              const char *fromValue);

template <typename T>
void setToIni(IniFile &iniFile, const char *section, const char *key,
              T fromValue);

template <typename T>
void setToIni(IniFile &iniFile, const char *section, const char *key,
              T *fromValueArr, const int &size);
```

### json

Based On `json` --- [Github](https://github.com/nlohmann/json)

```cxx
struct JsonFile {
  string path;
  json data;
};

bool readDataFromJsonFile(JsonFile &jsonFile);

void getFromJsonData(const JsonFile &jsonFile, const string &key,
                     string &param, string defaultVal);

template <typename T>
void getFromJsonData(const JsonFile &jsonFile, const string &key, T &param,
                     T defaultVal);

void getFromJsonData(const JsonFile &jsonFile, const string &key,
                     string *param, string *defaultVal, const int &size);

template <typename T>
void getFromJsonData(const JsonFile &jsonFile, const string &key, T *param,
                     T *defaultVal, const int &size);
```

### dat

```cxx
struct DatFile {
  string path;
  vector<char> data;
};

bool readDatFile(DatFile &datFile);

bool readDatFile(DatFile &datFile, char *varibale, const int &num);

bool writeDataToDatFile(const DatFile &datFile);
```

### bmp

Just read this file --- [BMP.h](./bmp/BMP.h)

```cxx
struct BmpFile {
  string path;
};
```