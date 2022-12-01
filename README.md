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

### txt

```cxx
struct TxtFile {
  std::string path;
  std::string data = "";
};

bool readTxtFileLine(TxtFile &txtFile);

bool writeDataToTxtFile(TxtFile &txtFile, std::string data);
```

### ini

Based On `simpleini` --- [Github](https://github.com/brofield/simpleini)

```cxx
struct IniFile {
  std::string path;
};

bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  std::string &param, const char *defaultVal);

template <typename T>
bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T &param, T defaultVal);

template <typename T>
bool getFromIni(const IniFile &iniFile, const char *section, const char *key,
                  T *param, T *defaultVal, const int &size);

bool setToIni(const IniFile &iniFile, const char *section, const char *key,
                const char *fromValue);

template <typename T>
bool setToIni(const IniFile &iniFile, const char *section, const char *key,
                T fromValue);

template <typename T>
bool setToIni(const IniFile &iniFile, const char *section, const char *key,
                T *fromValueArr, const int &size);
```

### json

Based On `jsoncpp` --- [Github](https://github.com/open-source-parsers/jsoncpp)

```cxx
struct JsonFile {
  std::string path;
  Json::Value data;
};

bool readDataFromJsonFile(JsonFile &jsonFile);

void getFromJsonData(const JsonFile &jsonFile, const std::string &key,
                       std::string &param, std::string defaultVal);

template <typename T>
void getFromJsonData(const JsonFile &jsonFile, const std::string &key,
                       T &param, T defaultVal);

void getFromJsonData(const JsonFile &jsonFile, const std::string &key,
                       std::string *param, std::string *defaultVal,
                       const int &size);

template <typename T>
void getFromJsonData(const JsonFile &jsonFile, const std::string &key,
                       T *param, T *defaultVal, const int &size);
```

### dat

```cxx
struct DatFile {
  std::string path;
  std::vector<char> data;
};

bool readDatFile(DatFile &datFile);

bool readDatFile(DatFile &datFile, char *varibale, const int &num);

bool writeDataToDatFile(const DatFile &datFile);
```