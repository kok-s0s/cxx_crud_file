#include "pch.h"

FileTools fileTools;

TEST(txtFile_Test, readTxtFileLine) {
  TxtFile txt_test_01;
  txt_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\test_01.txt";

  EXPECT_EQ(txt_test_01.path,
            "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\test_01.txt");
  EXPECT_EQ(fileTools.readTxtFileLine(txt_test_01), true);
  EXPECT_EQ(txt_test_01.data, "kok-s0s\ni like code.\n");
}

TEST(txtFile_Test, writeDataToTxtFile) {
  TxtFile txt_test_02;
  txt_test_02.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\test_02.txt";
  std::string data = "hei\nare you ok?\n";

  EXPECT_EQ(txt_test_02.path,
            "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\test_02.txt");
  EXPECT_EQ(fileTools.writeDataToTxtFile(txt_test_02, data), true);
  EXPECT_EQ(txt_test_02.data, "hei\nare you ok?\n");
}
