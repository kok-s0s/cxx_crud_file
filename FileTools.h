#include <fstream>
#include <iostream>
#include <string>

struct TxtFile {
  std::string path;
  std::string data = "";
};

class FileTools {
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
};
