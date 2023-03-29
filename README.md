# cxx_crud_file

## Development environment

**VSCode extensions**

- `C/C++`
- `CMake`
- `CMake Tools`
- `clang-format`
- `Hex Editor`

## Test-Driven Development (TDD)

[GoogleTest](http://google.github.io/googletest/quickstart-cmake.html)

## Project structure

### Source code

- [Tools.hpp](./Tools.hpp)
- [UFile.hpp](./UFile.hpp)
  - [BinFile.hpp](./BinFile.hpp)
  - [BmpFile.hpp](./BmpFile.hpp)
    - [BMP.h](./bmp/BMP.h)
  - [IniFile.hpp](./IniFile.hpp)
    - [SimpleIni.h](./ini/SimpleIni.h)
  - [JsonFile.hpp](./JsonFile.hpp)
    - [json.hpp](./json/json.hpp)
  - [TxtFile.hpp](./TxtFile.hpp)
- [UString.hpp](./UString.hpp)
- [Variant.hpp](./Variant.hpp)

### Test

- [main.cpp](./main.cpp)
- [test_files](./test_files)

### Other

- [.clang-format](./.clang-format)
- [CMakeLists.txt](./CMakeLists.txt)

## Static C/C++ Code Analysis

[CppCheck](http://cppcheck.sourceforge.net/)
