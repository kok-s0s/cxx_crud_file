# FileIO Utility Library

This C++ utility library provides classes for reading and writing various file formats.

## Key Classes

| Class    | Description                                    |
| -------- | ---------------------------------------------- |
| TxtFile  | Read and write text files.                     |
| IniFile  | Read and write INI files.                      |
| JsonFile | Read and write JSON files.                     |
| BinFile  | Read and write binary files.                   |
| BmpFile  | Read BMP image files. Copy BMP files.          |
| UString  | String formatting utility.                     |
| Variant  | Holds various data types in a single variable. |

## Usage

1. Include the necessary headers.
2. Instantiate the desired file class.
3. Use provided methods for file operations.
4. Optionally, use additional tools like `UString` or `Variant`.

## Testing

Google Test framework is used for testing to ensure the correct functionality of each file type and utility.
