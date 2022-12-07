#include "FileTools.hpp"
#include <gtest/gtest.h>
#include <iostream>

FileTools fileTools;

#pragma region path

TEST(path_Test, mergePathArgs) {
  string arg_01 = "C:";
  string arg_02 = "home";
  string arg_03 = "kok-s0s";

  EXPECT_EQ(fileTools.mergePathArgs(arg_01, arg_02, arg_03,
                                    "cxx_curd_file_unix", "main.cpp"),
            "C:/home/kok-s0s/cxx_curd_file_unix/main.cpp");
}

TEST(path_Test, pathExistFlag) {
  string path_01 =
      fileTools.get_current_directory() + "/files_test/test_01.txt";
  string path_02 =
      fileTools.get_current_directory() + "/files_test/test_10.txt";

  EXPECT_EQ(fileTools.pathExistFlag(path_01), true);
  EXPECT_EQ(fileTools.pathExistFlag(path_02), false);
}

#pragma endregion

#pragma region txtTest

TEST(txtFile_Test, readTxtFileLine) {
  TxtFile txt_test_01;
  txt_test_01.path =
      fileTools.get_current_directory() + "/files_test/test_01.txt";

  EXPECT_EQ(fileTools.readTxtFileLine(txt_test_01), true);
  EXPECT_EQ(txt_test_01.data, "kok-s0s\ni like code.\n");
}

TEST(txtFile_Test, writeDataToTxtFile) {
  TxtFile txt_test_02;
  txt_test_02.path =
      fileTools.get_current_directory() + "/files_test/test_02.txt";

  std::string data = "hei\nare you ok?\n";

  EXPECT_EQ(fileTools.writeDataToTxtFile(txt_test_02, data), true);
  EXPECT_EQ(txt_test_02.data, "hei\nare you ok?\n");
}

#pragma endregion

#pragma region iniTest

TEST(iniFile_Test, iniSetup) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);
}

TEST(iniFile_Test, getStringFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  std::string str_value_01;
  std::string str_value_02;
  std::string str_value_03;

  fileTools.getFromIni(ini_test_01, "string", "str1", str_value_01, "qi");
  fileTools.getFromIni(ini_test_01, "string", "str2", str_value_02, "qi");
  fileTools.getFromIni(ini_test_01, "string", "str3", str_value_03, "qi");

  EXPECT_EQ(str_value_01, "kok-s0s");
  EXPECT_EQ(str_value_02, "hello");
  EXPECT_EQ(str_value_03, "qi");
}

TEST(iniFile_Test, getIntFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  int int_value_01;
  int int_value_02;
  int int_value_03;

  fileTools.getFromIni(ini_test_01, "int", "int1", int_value_01, 19);
  fileTools.getFromIni(ini_test_01, "int", "int2", int_value_02, 19);
  fileTools.getFromIni(ini_test_01, "int", "int3", int_value_03, 19);

  EXPECT_EQ(int_value_01, 11);
  EXPECT_EQ(int_value_02, 8);
  EXPECT_EQ(int_value_03, 19);
}

TEST(iniFile_Test, getFloatFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  float float_value_01;
  float float_value_02;
  float float_value_03;

  fileTools.getFromIni(ini_test_01, "float", "float1", float_value_01, 22.09f);
  fileTools.getFromIni(ini_test_01, "float", "float2", float_value_02, 22.09f);
  fileTools.getFromIni(ini_test_01, "float", "float3", float_value_03, 22.09f);

  EXPECT_EQ(float_value_01, 33.33f);
  EXPECT_EQ(float_value_02, 22.22f);
  EXPECT_EQ(float_value_03, 22.09f);
}

TEST(iniFile_Test, getDoubleFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  double double_value_01;
  double double_value_02;
  double double_value_03;

  fileTools.getFromIni(ini_test_01, "double", "double1", double_value_01,
                       19.09);
  fileTools.getFromIni(ini_test_01, "double", "double2", double_value_02,
                       19.09);
  fileTools.getFromIni(ini_test_01, "double", "double3", double_value_03,
                       19.09);

  EXPECT_EQ(double_value_01, 3.14);
  EXPECT_EQ(double_value_02, 1.01);
  EXPECT_EQ(double_value_03, 19.09);
}

TEST(iniFile_Test, getBoolFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  bool bool_value_01;
  bool bool_value_02;
  bool bool_value_03;

  fileTools.getFromIni(ini_test_01, "bool", "bool1", bool_value_01, false);
  fileTools.getFromIni(ini_test_01, "bool", "bool2", bool_value_02, true);
  fileTools.getFromIni(ini_test_01, "bool", "bool3", bool_value_03, true);

  EXPECT_EQ(bool_value_01, true);
  EXPECT_EQ(bool_value_02, false);
  EXPECT_EQ(bool_value_03, true);
}

TEST(iniFile_Test, getArrayIntFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  int array_int[8];
  int array_int_testD[8];
  int default_array_int[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = 8;
  int right_array_int[] = {81, 71, 61, 51, 41, 31, 21, 11};

  fileTools.getFromIni(ini_test_01, "array", "arrayInt", array_int,
                       default_array_int, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int[i], right_array_int[i]);
  }

  fileTools.getFromIni(ini_test_01, "array", "arrayInt_testD", array_int_testD,
                       default_array_int, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int_testD[i], default_array_int[i]);
  }
}

TEST(iniFile_Test, getArrayFloatFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  float array_float[5];
  float array_float_testD[5];
  float default_array_float[] = {1.11f, 2.11f, 3.11f, 4.11f, 5.11f};
  int size = 5;
  float right_array_float[] = {1.1f, 2.1f, 3.1f, 4.1f, 5.1f};

  fileTools.getFromIni(ini_test_01, "array", "arrayFloat", array_float,
                       default_array_float, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_float[i], right_array_float[i]);
  }

  fileTools.getFromIni(ini_test_01, "array", "arrayFloat_testD",
                       array_float_testD, default_array_float, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_float_testD[i], default_array_float[i]);
  }
}

TEST(iniFile_Test, getArrayDoubleFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.get_current_directory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);

  double array_double[5];
  double array_double_testD[5];
  double default_array_double[] = {1.11, 2.11, 3.11, 4.11, 5.11};
  int size = 5;
  double right_array_double[] = {1.01, 2.01, 3.01, 4.01, 5.01};

  fileTools.getFromIni(ini_test_01, "array", "arrayDouble", array_double,
                       default_array_double, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_double[i], right_array_double[i]);
  }

  fileTools.getFromIni(ini_test_01, "array", "arrayDouble_testD",
                       array_double_testD, default_array_double, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_double_testD[i], default_array_double[i]);
  }
}

TEST(iniFile_Test, getFromIni_False) {
  IniFile ini_test_03;
  ini_test_03.path =
      fileTools.get_current_directory() + "/files_test/no_find.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_03), false);

  int int_value_01;
  int int_value_02;

  fileTools.getFromIni(ini_test_03, "int", "int1", int_value_01, 22);
  fileTools.getFromIni(ini_test_03, "int", "int2", int_value_02, 22);

  EXPECT_EQ(int_value_01, 22);
  EXPECT_EQ(int_value_02, 22);
}

TEST(iniFile_Test, setToIni) {
  IniFile ini_test_02;
  ini_test_02.path =
      fileTools.get_current_directory() + "/files_test/ini_test_02.ini";

  if (fileTools.iniSetup(ini_test_02)) {
    fileTools.setToIni(ini_test_02, "string", "str1", "kok-s0s");
    fileTools.setToIni(ini_test_02, "int", "int1", 22);
    fileTools.setToIni(ini_test_02, "float", "float1", 22.09f);
    fileTools.setToIni(ini_test_02, "double", "double1", 22.09);
    fileTools.setToIni(ini_test_02, "bool", "bool1", true);

    string output;
    ini_test_02.ini.Save(output);
    const char *path = (char *)ini_test_02.path.c_str();
    ini_test_02.ini.SaveFile(path);
  }
}

TEST(iniFile_Test, setArrayToIni) {
  IniFile ini_test_02;
  ini_test_02.path =
      fileTools.get_current_directory() + "/files_test/ini_test_02.ini";

  if (fileTools.iniSetup(ini_test_02)) {
    int arr_int[] = {2, 3, 4, 5, 6, 1};
    float arr_float[] = {1.01f, 2.01f, 3.01f};
    double arr_double[] = {2.11, 3.11, 1.11};

    fileTools.setToIni(ini_test_02, "intArr", "iArr", arr_int, 6);
    fileTools.setToIni(ini_test_02, "floatArr", "fArr", arr_float, 3);
    fileTools.setToIni(ini_test_02, "doubleArr", "dArr", arr_double, 3);

    string output;
    ini_test_02.ini.Save(output);
    const char *path = (char *)ini_test_02.path.c_str();
    ini_test_02.ini.SaveFile(path);
  }
}

#pragma endregion

#pragma region jsonTest

TEST(jsonFile_Test, readDataFromJsonFile) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_test.json";

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), true);
}

TEST(jsonFile_Test, getFromJsonData) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_test.json";

  std::string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  std::string depth_json_value_string;

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), true);

  fileTools.getFromJsonData(json_test, "encoding", json_value_string, "kkkkk");
  fileTools.getFromJsonData(json_test, "int", json_value_int, 19);
  fileTools.getFromJsonData(json_test, "double", json_value_double, 19.22);
  fileTools.getFromJsonData(json_test, "bool", json_value_bool, true);
  fileTools.getFromJsonData(json_test, "indent.length", depth_json_value_int,
                            19);
  fileTools.getFromJsonData(json_test, "indent.use_space",
                            depth_json_value_bool, false);
  fileTools.getFromJsonData(json_test, "indent.g", depth_json_value_string,
                            "bbbbb");

  EXPECT_EQ(json_value_string, "UTF-8");
  EXPECT_EQ(json_value_int, 22);
  EXPECT_EQ(json_value_double, 22.22);
  EXPECT_EQ(json_value_bool, false);
  EXPECT_EQ(depth_json_value_int, 3);
  EXPECT_EQ(depth_json_value_bool, true);
  EXPECT_EQ(depth_json_value_string, "ekoko");
}

TEST(jsonFile_Test, getStringArrFromJsonData) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_test.json";

  std::string json_value[3];
  std::string json_target_value[] = {"python", "c++", "ruby"};
  std::string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), true);
  fileTools.getFromJsonData(json_test, "plug-ins", json_value,
                            json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(jsonFile_Test, getIntArrFromJsonData) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_test.json";

  int json_value[3];
  int json_target_value[] = {1, 2, 3};
  int json_default_value[] = {3, 2, 1};
  int size = 3;

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), true);
  fileTools.getFromJsonData(json_test, "indent.int_arr", json_value,
                            json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(jsonFile_Test, getDoubleArrFromJsonData) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_test.json";

  double json_value[3];
  double json_target_value[] = {1.11, 2.11, 3.11};
  double json_default_value[] = {3.11, 2.11, 1.11};
  int size = 3;

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), true);
  fileTools.getFromJsonData(json_test, "indent.double_arr", json_value,
                            json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(jsonFile_Test, getFromJsonData_False) {
  JsonFile json_test;
  json_test.path =
      fileTools.get_current_directory() + "/files_test/json_false.json";

  std::string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  std::string depth_json_value_string;
  std::string json_value[3];
  std::string json_target_value[] = {"python", "c++", "ruby"};
  std::string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_EQ(fileTools.readDataFromJsonFile(json_test), false);

  fileTools.getFromJsonData(json_test, "encoding", json_value_string, "kkkkk");
  fileTools.getFromJsonData(json_test, "int", json_value_int, 19);
  fileTools.getFromJsonData(json_test, "double", json_value_double, 19.22);
  fileTools.getFromJsonData(json_test, "bool", json_value_bool, true);
  fileTools.getFromJsonData(json_test, "indent.length", depth_json_value_int,
                            19);
  fileTools.getFromJsonData(json_test, "indent.use_space",
                            depth_json_value_bool, false);
  fileTools.getFromJsonData(json_test, "indent.g", depth_json_value_string,
                            "bbbbb");
  fileTools.getFromJsonData(json_test, "plug-ins", json_value,
                            json_default_value, size);

  EXPECT_EQ(json_value_string, "kkkkk");
  EXPECT_EQ(json_value_int, 19);
  EXPECT_EQ(json_value_double, 19.22);
  EXPECT_EQ(json_value_bool, true);
  EXPECT_EQ(depth_json_value_int, 19);
  EXPECT_EQ(depth_json_value_bool, false);
  EXPECT_EQ(depth_json_value_string, "bbbbb");

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_default_value[i]);
  }
}

#pragma endregion

#pragma region dat

TEST(datFile_Test, readDatFile) {
  DatFile dat_test;
  dat_test.path =
      fileTools.get_current_directory() + "/files_test/dat_test.dat";

  EXPECT_EQ(fileTools.readDatFile(dat_test), true);
}

TEST(datFile_Test, readDatFileToPtr) {
  DatFile dat_test;
  dat_test.path =
      fileTools.get_current_directory() + "/files_test/dat_test.dat";

  long dataSize = 8192;
  int num = dataSize / sizeof(char);
  char *variable = (char *)malloc(sizeof(char) * num);

  if (fileTools.readDatFile(dat_test, variable, num)) {
    EXPECT_EQ((int)variable[0], -87);
  }
}

TEST(datFile_Test, writeDataToDatFile) {
  DatFile dat_test;
  dat_test.path =
      fileTools.get_current_directory() + "/files_test/dat_test.dat";

  if (fileTools.readDatFile(dat_test)) {
    DatFile dat_test_copy = dat_test;
    dat_test_copy.path =
        fileTools.get_current_directory() + "/files_test/dat_test_copy.dat";
    EXPECT_EQ(fileTools.writeDataToDatFile(dat_test_copy), true);
  }
}

#pragma endregion