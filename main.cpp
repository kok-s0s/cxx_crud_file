#include <gtest/gtest.h>

#include <iostream>

#include "FileTools.hpp"
#include "UFile.hpp"
#include "UString.hpp"

FileTools fileTools;

#pragma region directory

TEST(directory, create_directory) {
  string currentDirectory = fileTools.getCurrentDirectory();
  string newDir = currentDirectory + "/files_test/hello";

  if (!fileTools.pathExists(newDir)) fileTools.createDirectory(newDir);

  EXPECT_EQ(fileTools.pathExists(newDir), true);
}

TEST(directory, create_multi_level_directory) {}

TEST(directory, delete_directory) {
  string currentDirectory = fileTools.getCurrentDirectory();
  string newDir = currentDirectory + "/files_test/hello_d";

  fileTools.createDirectory(newDir);

  EXPECT_EQ(fileTools.pathExists(newDir), true);

  fileTools.deleteDirectory(newDir);

  EXPECT_EQ(fileTools.pathExists(newDir), false);
}

TEST(directory, get_current_directory) {
  EXPECT_EQ(fileTools.getCurrentDirectory(
                "C:/home/kok-s0s/cxx_curd_file_unix/main.cpp"),
            "C:/home/kok-s0s/cxx_curd_file_unix");
}

#pragma endregion

#pragma region path

TEST(path, is_path_exist) {
  string path_01 = fileTools.getCurrentDirectory() + "/files_test/test_01.txt";
  string path_02 = fileTools.getCurrentDirectory() + "/files_test/test_10.txt";

  EXPECT_EQ(fileTools.pathExists(path_01), true);
  EXPECT_EQ(fileTools.pathExists(path_02), false);
}

#pragma endregion

#pragma region txt

TEST(txt, read_data_from_txt) {
  TxtFile txt_test_01;
  txt_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/test_01.txt";

  EXPECT_EQ(fileTools.readDataFromTxtFile(txt_test_01), true);
  EXPECT_EQ(txt_test_01.data, "kok-s0s\ni like code.\n");
}

TEST(txt, write_data_to_txt) {
  TxtFile txt_test_02;
  txt_test_02.path =
      fileTools.getCurrentDirectory() + "/files_test/test_02.txt";

  txt_test_02.data = "hei\nare you ok?\n";

  EXPECT_EQ(fileTools.writeDataToTxtFile(txt_test_02), true);
  EXPECT_EQ(txt_test_02.data, "hei\nare you ok?\n");
}

#pragma endregion

#pragma region ini

TEST(ini, ini_setup) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_01), true);
}

TEST(ini, get_string_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_int_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_float_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_double_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_bool_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_array_int_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_array_float_data_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_array_double_from_ini) {
  IniFile ini_test_01;
  ini_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";

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

TEST(ini, get_data_from_ini_false_case) {
  IniFile ini_test_03;
  ini_test_03.path =
      fileTools.getCurrentDirectory() + "/files_test/no_find.ini";

  EXPECT_EQ(fileTools.iniSetup(ini_test_03), false);

  int int_value_01;
  int int_value_02;

  fileTools.getFromIni(ini_test_03, "int", "int1", int_value_01, 22);
  fileTools.getFromIni(ini_test_03, "int", "int2", int_value_02, 22);

  EXPECT_EQ(int_value_01, 22);
  EXPECT_EQ(int_value_02, 22);
}

TEST(ini, set_data_to_ini) {
  IniFile ini_test_02;
  ini_test_02.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_02.ini";

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

TEST(ini, set_array_data_to_ini) {
  IniFile ini_test_02;
  ini_test_02.path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_02.ini";

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

#pragma region json

TEST(json, json_setup) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";

  EXPECT_EQ(fileTools.jsonSetup(json_test), true);
}

TEST(json, get_data_from_json) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";

  std::string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  std::string depth_json_value_string;

  EXPECT_EQ(fileTools.jsonSetup(json_test), true);

  fileTools.getFromJson(json_test, "encoding", json_value_string, "kkkkk");
  fileTools.getFromJson(json_test, "int", json_value_int, 19);
  fileTools.getFromJson(json_test, "double", json_value_double, 19.22);
  fileTools.getFromJson(json_test, "bool", json_value_bool, true);
  fileTools.getFromJson(json_test, "indent.length", depth_json_value_int, 19);
  fileTools.getFromJson(json_test, "indent.use_space", depth_json_value_bool,
                        false);
  fileTools.getFromJson(json_test, "indent.g", depth_json_value_string,
                        "bbbbb");

  EXPECT_EQ(json_value_string, "UTF-8");
  EXPECT_EQ(json_value_int, 22);
  EXPECT_EQ(json_value_double, 22.22);
  EXPECT_EQ(json_value_bool, false);
  EXPECT_EQ(depth_json_value_int, 3);
  EXPECT_EQ(depth_json_value_bool, true);
  EXPECT_EQ(depth_json_value_string, "ekoko");
}

TEST(json, get_array_string_data_from_json) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";

  std::string json_value[3];
  std::string json_target_value[] = {"python", "c++", "ruby"};
  std::string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_EQ(fileTools.jsonSetup(json_test), true);
  fileTools.getFromJson(json_test, "plug-ins", json_value, json_default_value,
                        size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_int_data_from_json) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";

  int json_value[3];
  int json_target_value[] = {1, 2, 3};
  int json_default_value[] = {3, 2, 1};
  int size = 3;

  EXPECT_EQ(fileTools.jsonSetup(json_test), true);
  fileTools.getFromJson(json_test, "indent.int_arr", json_value,
                        json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_double_data_from_json) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";

  double json_value[3];
  double json_target_value[] = {1.11, 2.11, 3.11};
  double json_default_value[] = {3.11, 2.11, 1.11};
  int size = 3;

  EXPECT_EQ(fileTools.jsonSetup(json_test), true);
  fileTools.getFromJson(json_test, "indent.double_arr", json_value,
                        json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_data_from_Json_false_case) {
  JsonFile json_test;
  json_test.path =
      fileTools.getCurrentDirectory() + "/files_test/json_false.json";

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

  EXPECT_EQ(fileTools.jsonSetup(json_test), false);

  fileTools.getFromJson(json_test, "encoding", json_value_string, "kkkkk");
  fileTools.getFromJson(json_test, "int", json_value_int, 19);
  fileTools.getFromJson(json_test, "double", json_value_double, 19.22);
  fileTools.getFromJson(json_test, "bool", json_value_bool, true);
  fileTools.getFromJson(json_test, "indent.length", depth_json_value_int, 19);
  fileTools.getFromJson(json_test, "indent.use_space", depth_json_value_bool,
                        false);
  fileTools.getFromJson(json_test, "indent.g", depth_json_value_string,
                        "bbbbb");
  fileTools.getFromJson(json_test, "plug-ins", json_value, json_default_value,
                        size);

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

TEST(json, set_data_to_json) {
  JsonFile store_json;
  store_json.path =
      fileTools.getCurrentDirectory() + "/files_test/store_json.json";

  int a[10] = {0};

  store_json.data["nickname"] = "kok-s0s";
  store_json.data["birthday"] = "0219";
  store_json.data["array"] = a;

  json sub;

  sub["work"] = "C++ Dev";

  store_json.data["subJson"] = sub;

  std::ofstream file(store_json.path);
  file << store_json.data;
  file.flush();
}

#pragma endregion

#pragma region dat

TEST(dat, read_data_from_dat) {
  DatFile dat_test;
  dat_test.path = fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";

  EXPECT_EQ(fileTools.readDatFile(dat_test), true);
}

TEST(dat, read_data_from_dat_and_set_to_pointer_variable) {
  string datFilePath =
      fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";

  long dataSize = 8192;
  int num = dataSize / sizeof(char);
  unsigned char *variable =
      (unsigned char *)malloc(sizeof(unsigned char) * num);

  if (fileTools.readDatFile(datFilePath, variable, num)) {
    EXPECT_EQ((unsigned int)variable[0], 169);
  }
}

TEST(dat, write_data_to_dat) {
  DatFile dat_test;
  dat_test.path = fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";

  if (fileTools.readDatFile(dat_test)) {
    DatFile dat_test_copy = dat_test;
    dat_test_copy.path =
        fileTools.getCurrentDirectory() + "/files_test/dat_test_copy.dat";
    EXPECT_EQ(fileTools.writeDataToDatFile(dat_test_copy), true);
  }
}

TEST(dat, append_write_data_to_dat) {
  DatFile dat_test;
  dat_test.path = fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";

  if (fileTools.readDatFile(dat_test)) {
    DatFile dat_test_twice = dat_test;
    dat_test_twice.path =
        fileTools.getCurrentDirectory() + "/files_test/dat_test_twice.dat";

    EXPECT_EQ(fileTools.writeDataToDatFile(dat_test_twice), true);
    EXPECT_EQ(fileTools.appendWriteDataToDatFile(dat_test_twice.path,
                                                 &dat_test_twice.data[0],
                                                 dat_test_twice.data.size()),
              true);
  }
}

TEST(dat, save_output_data_to_dat) {
  string datFilePath =
      fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";

  long dataSize = 8192;
  int num = dataSize / sizeof(char);
  unsigned char *variable = (unsigned char *)malloc(sizeof(char) * num);

  if (fileTools.readDatFile(datFilePath, variable, num)) {
    string dat_test_ptr =
        fileTools.getCurrentDirectory() + "/files_test/dat_test_ptr.dat";

    unsigned char *data = variable;

    int extData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_EQ(fileTools.saveOutputData(extData, 10, dat_test_ptr, data, 8192),
              true);
  }
}

#pragma endregion

#pragma region bmp

TEST(bmp, read_data_from_bmp) {
  BmpFile bmp_test_01;
  BmpFile bmp_test_02;
  bmp_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/bmp_test_01.bmp";
  bmp_test_02.path =
      fileTools.getCurrentDirectory() + "/files_test/bmp_test_02.bmp";

  BMP bmpObject_01(bmp_test_01.path.c_str());
  BMP bmpObject_02(bmp_test_02.path.c_str());

  EXPECT_EQ(bmpObject_01.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_01.bmp_info_header.width, 128);
  EXPECT_EQ(bmpObject_02.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_02.bmp_info_header.width, 16);
}

TEST(bmp, copy_bmp) {
  BmpFile bmp_test_01;
  bmp_test_01.path =
      fileTools.getCurrentDirectory() + "/files_test/bmp_test_01.bmp";

  string copy_bmp_file =
      fileTools.getCurrentDirectory() + "/files_test/copy_bmp.bmp";

  BMP bmpObject(bmp_test_01.path.c_str());
  bmpObject.write(copy_bmp_file.c_str());

  BMP bmpObject_copy(copy_bmp_file.c_str());
  EXPECT_EQ(bmpObject_copy.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_copy.bmp_info_header.width, 128);
}

#pragma endregion

#pragma region common

TEST(common, copy) {
  string txt_path = fileTools.getCurrentDirectory() + "/files_test/test_01.txt";
  string copy_txt_path =
      fileTools.getCurrentDirectory() + "/files_test/copy_test_01.txt";

  EXPECT_EQ(fileTools.copy(txt_path, copy_txt_path), true);

  string ini_path =
      fileTools.getCurrentDirectory() + "/files_test/ini_test_01.ini";
  string copy_ini_path =
      fileTools.getCurrentDirectory() + "/files_test/copy_ini_test_01.ini";

  EXPECT_EQ(fileTools.copy(ini_path, copy_ini_path), true);

  string json_path =
      fileTools.getCurrentDirectory() + "/files_test/json_test.json";
  string copy_json_path =
      fileTools.getCurrentDirectory() + "/files_test/copy_json_test.json";

  EXPECT_EQ(fileTools.copy(json_path, copy_json_path), true);

  string dat_path =
      fileTools.getCurrentDirectory() + "/files_test/dat_test.dat";
  string copy_dat_path =
      fileTools.getCurrentDirectory() + "/files_test/copy_dat_test.json";

  EXPECT_EQ(fileTools.copy(dat_path, copy_dat_path), true);

  string bmp_path =
      fileTools.getCurrentDirectory() + "/files_test/bmp_test_01.bmp";
  string copy_bmp_path =
      fileTools.getCurrentDirectory() + "/files_test/copy_bmp_test_01.bmp";

  EXPECT_EQ(fileTools.copy(bmp_path, copy_bmp_path), true);
}

#pragma endregion

#pragma region UString

TEST(UString, use_string_as_params) {
  string arg_01 = "test";
  string arg_02 = "folder";
  string arg_03 = "cpp";

  string path = UString("C:/home/%1/%2/%3/hello.c")
                    .args(arg_01)
                    .args(arg_02)
                    .args(arg_03);

  EXPECT_EQ(path, "C:/home/test/folder/cpp/hello.c");
}

TEST(UString, use_int_as_params) {
  string arg_01 = "test";
  int arg_02 = 1;
  string arg_03 = "text";

  string path =
      UString("C:/home/%1/%2/%3.txt").args(arg_01).args(arg_02).args(arg_03);

  EXPECT_EQ(path, "C:/home/test/1/text.txt");
}

TEST(UString, use_define_variable_as_params) {
  string arg_01 = "test";
  int arg_02 = 1;
#define HOME "home"

  string path = UString("C:/%1/%2/%3/%4/%5.txt")
                    .args(HOME, arg_01, arg_02, "default", "text");

  EXPECT_EQ(path, "C:/home/test/1/default/text.txt");
}

TEST(UString, loop_params) {
  string arg_01 = "test";
  int arg_02 = 1;

  string path = UString("C:/home/%1/%2/%3.txt").args(arg_01, arg_02, "text");

  EXPECT_EQ(path, "C:/home/test/1/text.txt");
}

TEST(UString, left_value) {
  string arg_01 = "test";
  int arg_02 = 1;

  std::cout << UString("C:/home/%1/%2/%3.txt").args(arg_01, arg_02, "text")
            << std::endl;
}

#pragma endregion

#pragma region file

TEST(file, exist) {
  string path_01 = fileTools.getCurrentDirectory() + "/files_test/test_01.txt";
  string path_02 = fileTools.getCurrentDirectory() + "/files_test/test_10.txt";

  EXPECT_EQ(fs::exists(UFile(path_01).handle()), true);
  EXPECT_EQ(fs::exists(UFile(path_02).handle()), false);
}

TEST(file, get_file_size) {
  fs::path p = fs::current_path() / "example.bin";
  UFile file = UFile(p);

  std::ofstream(p) << "kok-s0s";  // create file of size 7

  EXPECT_EQ(fs::file_size(file.handle()), 7);

  fs::remove(p);
}

TEST(file, get_absolute_path) {
  fs::path p = fs::current_path() / "test.txt";
  UFile file = UFile(p);

  std::ofstream(p) << "kok-s0s";  // create file of size 7

  EXPECT_EQ(fs::absolute(file.handle()), p);
}

TEST(file, delete_file) {
  fs::path p = fs::current_path() / "hello.cpp";
  UFile file = UFile(p);

  std::ofstream(p) << "world";

  EXPECT_EQ(fs::file_size(file.handle()), 5);

  EXPECT_EQ(fs::remove(p), true);
}

TEST(file, if_file_exist_then_find_its_father_directory) {}

TEST(file, copy) {}

TEST(file, use_file_as_params) {}

#pragma endregion