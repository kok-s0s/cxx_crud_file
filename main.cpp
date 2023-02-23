#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "BmpFile.hpp"
#include "DatFile.hpp"
#include "ImgFile.hpp"
#include "IniFile.hpp"
#include "JsonFile.hpp"
#include "TxtFile.hpp"
#include "UString.hpp"
#include "Variant.hpp"

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::to_string;
using std::vector;

#pragma region TxtFile

TEST(txt, read_data) {
  TxtFile test_01(fs::current_path() / "files_test/test_01.txt");

  EXPECT_TRUE(test_01.readData());
  EXPECT_EQ(test_01.getData(), "name\ni like code.\n");
}

TEST(txt, write_data) {
  TxtFile test_02(fs::current_path() / "files_test/test_02.txt");

  test_02.setData("hei\nare you ok?\n");

  EXPECT_TRUE(test_02.writeData());
  EXPECT_TRUE(test_02.readData());
  EXPECT_EQ(test_02.getData(), "hei\nare you ok?\n");
}

TEST(txt, append_write_data) {
  TxtFile test_03(fs::current_path() / "files_test/test_03.txt");

  test_03.setData("hello!\n");

  EXPECT_TRUE(test_03.writeData());
  EXPECT_TRUE(test_03.appendWriteData("hello!\n"));
  EXPECT_TRUE(test_03.readData());
  EXPECT_EQ(test_03.getData(), "hello!\nhello!\n");
}

#pragma endregion

#pragma region IniFile

TEST(ini, ini_setup) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());
}

TEST(ini, get_string) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  string str_value_01;
  string str_value_02;
  string str_value_03;

  test_01.getFromIni("string", "str1", str_value_01, "qi");
  test_01.getFromIni("string", "str2", str_value_02, "qi");
  test_01.getFromIni("string", "str3", str_value_03, "qi");

  EXPECT_EQ(str_value_01, "name");
  EXPECT_EQ(str_value_02, "hello");
  EXPECT_EQ(str_value_03, "qi");
}

TEST(ini, get_int) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  int int_value_01;
  int int_value_02;
  int int_value_03;

  test_01.getFromIni("int", "int1", int_value_01, 19);
  test_01.getFromIni("int", "int2", int_value_02, 19);
  test_01.getFromIni("int", "int3", int_value_03, 19);

  EXPECT_EQ(int_value_01, 11);
  EXPECT_EQ(int_value_02, 8);
  EXPECT_EQ(int_value_03, 19);
}

TEST(ini, get_float) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  float float_value_01;
  float float_value_02;
  float float_value_03;

  test_01.getFromIni("float", "float1", float_value_01, 22.09f);
  test_01.getFromIni("float", "float2", float_value_02, 22.09f);
  test_01.getFromIni("float", "float3", float_value_03, 22.09f);

  EXPECT_FLOAT_EQ(float_value_01, 33.33f);
  EXPECT_FLOAT_EQ(float_value_02, 22.22f);
  EXPECT_FLOAT_EQ(float_value_03, 22.09f);
}

TEST(ini, get_double) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  double double_value_01;
  double double_value_02;
  double double_value_03;

  test_01.getFromIni("double", "double1", double_value_01, 19.09);
  test_01.getFromIni("double", "double2", double_value_02, 19.09);
  test_01.getFromIni("double", "double3", double_value_03, 19.09);

  EXPECT_DOUBLE_EQ(double_value_01, 3.14);
  EXPECT_DOUBLE_EQ(double_value_02, 1.01);
  EXPECT_DOUBLE_EQ(double_value_03, 19.09);
}

TEST(ini, get_bool) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  bool bool_value_01;
  bool bool_value_02;
  bool bool_value_03;

  test_01.getFromIni("bool", "bool1", bool_value_01, false);
  test_01.getFromIni("bool", "bool2", bool_value_02, true);
  test_01.getFromIni("bool", "bool3", bool_value_03, true);

  EXPECT_EQ(bool_value_01, true);
  EXPECT_EQ(bool_value_02, false);
  EXPECT_EQ(bool_value_03, true);
}

TEST(ini, get_array_int) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  int array_int[8];
  int array_int_testD[8];
  int default_array_int[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = 8;
  int right_array_int[] = {81, 71, 61, 51, 41, 31, 21, 11};

  test_01.getFromIni("array", "arrayInt", array_int, default_array_int, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int[i], right_array_int[i]);
  }

  test_01.getFromIni("array", "arrayInt_testD", array_int_testD,
                     default_array_int, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int_testD[i], default_array_int[i]);
  }
}

TEST(ini, get_array_float) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  float array_float[5];
  float array_float_testD[5];
  float default_array_float[] = {1.11f, 2.11f, 3.11f, 4.11f, 5.11f};
  int size = 5;
  float right_array_float[] = {1.1f, 2.1f, 3.1f, 4.1f, 5.1f};

  test_01.getFromIni("array", "arrayFloat", array_float, default_array_float,
                     size);
  for (int i = 0; i < size; ++i) {
    EXPECT_FLOAT_EQ(array_float[i], right_array_float[i]);
  }

  test_01.getFromIni("array", "arrayFloat_testD", array_float_testD,
                     default_array_float, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_FLOAT_EQ(array_float_testD[i], default_array_float[i]);
  }
}

TEST(ini, get_array_double) {
  IniFile test_01(fs::current_path() / "files_test/ini_test_01.ini");

  EXPECT_TRUE(test_01.iniSetup());

  double array_double[5];
  double array_double_testD[5];
  double default_array_double[] = {1.11, 2.11, 3.11, 4.11, 5.11};
  int size = 5;
  double right_array_double[] = {1.01, 2.01, 3.01, 4.01, 5.01};

  test_01.getFromIni("array", "arrayDouble", array_double, default_array_double,
                     size);
  for (int i = 0; i < size; ++i) {
    EXPECT_DOUBLE_EQ(array_double[i], right_array_double[i]);
  }

  test_01.getFromIni("array", "arrayDouble_testD", array_double_testD,
                     default_array_double, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_DOUBLE_EQ(array_double_testD[i], default_array_double[i]);
  }
}

TEST(ini, get_false_case) {
  IniFile test_03(fs::current_path() / "files_test/no_find.ini");

  EXPECT_FALSE(test_03.iniSetup());

  int int_value_01;
  int int_value_02;

  test_03.getFromIni("int", "int1", int_value_01, 22);
  test_03.getFromIni("int", "int2", int_value_02, 22);

  EXPECT_EQ(int_value_01, 22);
  EXPECT_EQ(int_value_02, 22);
}

TEST(ini, set_data) {
  IniFile test_02(fs::current_path() / "files_test/ini_test_02.ini");

  if (test_02.iniSetup()) {
    test_02.setToIni("string", "str1", "name");
    test_02.setToIni("int", "int1", 22);
    test_02.setToIni("float", "float1", 22.09f);
    test_02.setToIni("double", "double1", 22.09);
    test_02.setToIni("bool", "bool1", true);

    test_02.save();
  }
}

TEST(ini, set_array_data) {
  IniFile test_02(fs::current_path() / "files_test/ini_test_02.ini");

  if (test_02.iniSetup()) {
    int arr_int[] = {2, 3, 4, 5, 6, 1};
    float arr_float[] = {1.01f, 2.01f, 3.01f};
    double arr_double[] = {2.11, 3.11, 1.11};

    test_02.setToIni("intArr", "iArr", arr_int, 6);
    test_02.setToIni("floatArr", "fArr", arr_float, 3);
    test_02.setToIni("doubleArr", "dArr", arr_double, 3);

    test_02.save();
  }
}

#pragma endregion

#pragma region JsonFile

TEST(json, json_setup) {
  JsonFile test(fs::current_path() / "files_test/json_test.json");

  EXPECT_TRUE(test.jsonSetup());
}

TEST(json, get_data) {
  JsonFile test(fs::current_path() / "files_test/json_test.json");

  string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  string depth_json_value_string;

  EXPECT_TRUE(test.jsonSetup());

  test.getFromJson("encoding", json_value_string, "kkkkk");
  test.getFromJson("int", json_value_int, 19);
  test.getFromJson("double", json_value_double, 19.22);
  test.getFromJson("bool", json_value_bool, true);
  test.getFromJson("indent.length", depth_json_value_int, 19);
  test.getFromJson("indent.use_space", depth_json_value_bool, false);
  test.getFromJson("indent.g", depth_json_value_string, "bbbbb");

  EXPECT_EQ(json_value_string, "UTF-8");
  EXPECT_EQ(json_value_int, 22);
  EXPECT_EQ(json_value_double, 22.22);
  EXPECT_EQ(json_value_bool, false);
  EXPECT_EQ(depth_json_value_int, 3);
  EXPECT_EQ(depth_json_value_bool, true);
  EXPECT_EQ(depth_json_value_string, "ekoko");
}

TEST(json, get_array_string_data) {
  JsonFile test(fs::current_path() / "files_test/json_test.json");

  string json_value[3];
  string json_target_value[] = {"python", "c++", "ruby"};
  string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_TRUE(test.jsonSetup());
  test.getFromJson("plug-ins", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_int_data) {
  JsonFile test(fs::current_path() / "files_test/json_test.json");

  int json_value[3];
  int json_target_value[] = {1, 2, 3};
  int json_default_value[] = {3, 2, 1};
  int size = 3;

  EXPECT_TRUE(test.jsonSetup());
  test.getFromJson("indent.int_arr", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_double_data) {
  JsonFile test(fs::current_path() / "files_test/json_test.json");

  double json_value[3];
  double json_target_value[] = {1.11, 2.11, 3.11};
  double json_default_value[] = {3.11, 2.11, 1.11};
  int size = 3;

  EXPECT_TRUE(test.jsonSetup());
  test.getFromJson("indent.double_arr", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_data_from_Json_false_case) {
  JsonFile test(fs::current_path() / "files_test/json_false.json");

  string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  string depth_json_value_string;
  string json_value[3];
  string json_target_value[] = {"python", "c++", "ruby"};
  string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_FALSE(test.jsonSetup());

  test.getFromJson("encoding", json_value_string, "kkkkk");
  test.getFromJson("int", json_value_int, 19);
  test.getFromJson("double", json_value_double, 19.22);
  test.getFromJson("bool", json_value_bool, true);
  test.getFromJson("indent.length", depth_json_value_int, 19);
  test.getFromJson("indent.use_space", depth_json_value_bool, false);
  test.getFromJson("indent.g", depth_json_value_string, "bbbbb");
  test.getFromJson("plug-ins", json_value, json_default_value, size);

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

TEST(json, set_data) {
  JsonFile store_json(fs::current_path() / "files_test/store_json.json");

  int a[10] = {0};

  store_json._data["nickname"] = "name";
  store_json._data["birthday"] = "0219";
  store_json._data["array"] = a;

  json sub;

  sub["work"] = "C++ Dev";

  store_json._data["subJson"] = sub;

  store_json.save();
}

#pragma endregion

#pragma region DatFile

TEST(dat, read_data) {
  DatFile test(fs::current_path() / "files_test/dat_test.dat");

  EXPECT_TRUE(test.readData());
}

TEST(dat, write_data) {
  DatFile test(fs::current_path() / "files_test/dat_test.dat");

  if (test.readData()) {
    DatFile dat_test_copy = test;
    fs::path copy_p = fs::current_path() / "files_test/dat_test_copy.dat";
    dat_test_copy.setPath(copy_p);

    EXPECT_TRUE(dat_test_copy.writeData());
  }
}

TEST(dat, read_data_and_set_to_pointer_variable) {
  fs::path path = fs::current_path() / "files_test/dat_test.dat";
  string datFilePath = path.string();

  long dataSize = 8192;
  int num = dataSize / sizeof(char);
  unsigned char *variable =
      (unsigned char *)malloc(sizeof(unsigned char) * num);

  if (DatFile::readDatFile(datFilePath, variable, num)) {
    EXPECT_EQ((unsigned int)variable[0], 169);
  }
}

TEST(dat, append_write_data) {
  DatFile test(fs::current_path() / "files_test/dat_test.dat");

  if (test.readData()) {
    DatFile test_twice = test;
    test_twice.setPath(fs::current_path() / "files_test/dat_test_twice.dat");

    EXPECT_EQ(test_twice.getData()[0], 169);

    EXPECT_TRUE(test_twice.writeData());
    EXPECT_TRUE(DatFile::appendWriteDataToDatFile(test_twice.getPath(),
                                                  &test_twice.getData()[0],
                                                  test_twice.getData().size()));
  }
}

TEST(dat, save_output_data) {
  string datFilePath =
      (fs::current_path() / "files_test/dat_test.dat").string();

  long dataSize = 8192;
  int num = dataSize / sizeof(char);
  unsigned char *variable = (unsigned char *)malloc(sizeof(char) * num);

  if (DatFile::readDatFile(datFilePath, variable, num)) {
    string dat_test_appendAdd =
        (fs::current_path() / "files_test/dat_test_appendAdd.dat").string();

    unsigned char *data = variable;

    int extData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    EXPECT_EQ(
        DatFile::saveOutputData(extData, 10, dat_test_appendAdd, data, 8192),
        true);
  }
}

#pragma endregion

#pragma region BmpFile

TEST(bmp, read_data) {
  BmpFile bmp_test_01(fs::current_path() / "files_test/bmp_test_01.bmp");
  BmpFile bmp_test_02(fs::current_path() / "files_test/bmp_test_02.bmp");

  BMP bmpObject_01(bmp_test_01.getPath().c_str());
  BMP bmpObject_02(bmp_test_02.getPath().c_str());

  EXPECT_EQ(bmpObject_01.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_01.bmp_info_header.width, 128);
  EXPECT_EQ(bmpObject_02.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_02.bmp_info_header.width, 16);
}

TEST(bmp, copy_bmp) {
  BmpFile bmp_test_01(fs::current_path() / "files_test/bmp_test_01.bmp");

  string copy_bmp_file =
      (fs::current_path() / "files_test/copy_bmp.bmp").string();

  BMP bmpObject(bmp_test_01.getPath().c_str());
  bmpObject.write(copy_bmp_file.c_str());

  BMP bmpObject_copy(copy_bmp_file.c_str());
  EXPECT_EQ(bmpObject_copy.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_copy.bmp_info_header.width, 128);
}

#pragma endregion

#pragma region ImgFile

TEST(img, read_data) {
  string img_p = (fs::current_path() / "files_test/ocean.jpg").string();

  ImgFile file(img_p);

  EXPECT_TRUE(file.readData());
}

TEST(img, write_data) {
  ImgFile file(fs::current_path() / "files_test/ocean.jpg");

  if (file.readData()) {
    ImgFile copy_f = file;

    copy_f.setPath(fs::current_path() / "files_test/ocean_copy.jpg");
    EXPECT_TRUE(copy_f.writeData());
  }
}

TEST(img, write_data_2) {
  ImgFile file(fs::current_path() / "files_test/ocean.jpg");

  if (file.readData()) {
    ImgFile copy_f(fs::current_path() / "files_test/ocean_copy2.jpg");

    copy_f.setData(file.getData());
    copy_f.setLength(file.getLength());

    EXPECT_TRUE(copy_f.writeData());
  }
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

  cout << UString("C:/home/%1/%2/%3.txt").args(arg_01, arg_02, "text") << endl;
}

#pragma endregion

#pragma region Variant

TEST(variant, type) {
  vector<Variant> vec;
  vec = {true, 'c', 1, 1.2, "hello"};

  EXPECT_EQ(vec[0].toString(), "true");
  EXPECT_EQ(vec[1].toString(), "c");
  EXPECT_EQ(vec[2].toString(), "1");
  EXPECT_EQ(vec[3].toString(), "1.2");
  EXPECT_EQ(vec[4].toString(), "hello");
}
#pragma endregion

#pragma region file

TEST(file, exist) {
  fs::path path_01 = fs::current_path() / "files_test/test_01.txt";
  fs::path path_02 = fs::current_path() / "files_test/test_10.txt";

  EXPECT_TRUE(fs::exists(UFile(path_01).handle()));
  EXPECT_FALSE(fs::exists(UFile(path_02).handle()));
}

TEST(file, get_file_size) {
  fs::path p = fs::current_path() / "example.bin";
  UFile file = UFile(p);

  ofstream(p) << "hello world";  // create file of size 1

  EXPECT_EQ(fs::file_size(file.handle()), 11);

  // fs::remove(p);
}

TEST(file, get_absolute_path) {
  fs::path p = fs::current_path() / "test.txt";
  UFile file = UFile(p);

  ofstream(p) << "hello world";  // create file of size 11

  EXPECT_EQ(fs::absolute(file.handle()), p);
}

TEST(file, delete_file) {
  fs::path p = fs::current_path() / "hello.cpp";
  UFile file = UFile(p);

  ofstream(p) << "world";

  EXPECT_EQ(fs::file_size(file.handle()), 5);

  EXPECT_TRUE(fs::remove(p));
}

TEST(file, delete_directory) {
  fs::path d = (fs::current_path() / "files_test/hello_d");

  EXPECT_NE(fs::remove_all(d), 0);
}

TEST(file, if_file_exist_then_find_its_father_directory) {
  string path = (fs::current_path() / "files_test/test_01.txt").string();
  if (fs::exists(path)) {
    EXPECT_EQ(fs::path(path).parent_path(),
              (fs::current_path() / "files_test").string());
  }
}

TEST(file, find_its_father_directory) {
  string txt = (fs::current_path() / "files_txt/test_01.txt").string();
  if (!fs::exists(fs::path(txt).parent_path()))
    fs::create_directory(fs::path(txt).parent_path());
}

TEST(file, copy) {
  const auto copyOptions =
      fs::copy_options::update_existing | fs::copy_options::recursive;

  string txt_path = (fs::current_path() / "files_test/test_01.txt").string();
  string copy_txt_path =
      (fs::current_path() / "files_test/copy_test_01.txt").string();

  fs::copy(txt_path, copy_txt_path, copyOptions);

  string ini_path =
      (fs::current_path() / "files_test/ini_test_01.ini").string();
  string copy_ini_path =
      (fs::current_path() / "files_test/copy_ini_test_01.ini").string();

  fs::copy(ini_path, copy_ini_path, copyOptions);

  string json_path =
      (fs::current_path() / "files_test/json_test.json").string();
  string copy_json_path =
      (fs::current_path() / "files_test/copy_json_test.json").string();

  fs::copy(json_path, copy_json_path, copyOptions);

  string dat_path = (fs::current_path() / "files_test/dat_test.dat").string();
  string copy_dat_path =
      (fs::current_path() / "files_test/copy_dat_test.dat").string();

  fs::copy(dat_path, copy_dat_path, copyOptions);

  string bmp_path =
      (fs::current_path() / "files_test/bmp_test_01.bmp").string();
  string copy_bmp_path =
      (fs::current_path() / "files_test/copy_bmp_test_01.bmp").string();

  fs::copy(bmp_path, copy_bmp_path, copyOptions);
}

TEST(file, deleteReferFile_recursive) {
  string dir = (fs::current_path() / "sandbox").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt");
  ofstream(dir + "/a/file1.txt");
  ofstream(dir + "/a/b/file1.txt");

  UFile::deleteReferFile(dir, "file1.txt");
}

TEST(file, deleteReferFile) {
  string dir = (fs::current_path() / "sandbox2").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt");
  ofstream(dir + "/a/file1.txt");
  ofstream(dir + "/a/b/file1.txt");

  UFile::deleteReferFile(dir, "file1.txt", false);
}

TEST(file, copyFile_cover) {
  string dir = (fs::current_path() / "sandbox3").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt") << "file1.txt";
  ofstream(dir + "/a/file2.txt") << "file2.txt";
  ofstream(dir + "/a/b/file3.txt") << "file3.txt";

  UFile::copyFile(dir + "/file1.txt", dir + "/a/b/file3.txt", true);
}

TEST(file, copyFile) {
  string dir = (fs::current_path() / "sandbox6").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt") << "file1.txt";
  ofstream(dir + "/a/file2.txt") << "file2.txt";
  ofstream(dir + "/a/b/file3.txt") << "file3.txt";

  UFile::copyFile(dir + "/file1.txt", dir + "/a/b/file3.txt", false);
}

TEST(file, copyDirectoryFiles) {
  string dir = (fs::current_path() / "sandbox7").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt") << "file1.txt";
  ofstream(dir + "/a/file2.txt") << "file2.txt";
  ofstream(dir + "/a/b/file3.txt") << "file3.txt";

  string targetDir = (fs::current_path() / "sandbox9").string();

  UFile::copyDirectoryFiles(dir, targetDir, false);
}

TEST(file, copyDirectoryFiles_cover) {
  string dir = (fs::current_path() / "sandbox12").string();
  fs::create_directories(dir);
  fs::create_directories(dir + "/a/b");
  ofstream(dir + "/file1.txt") << "file11.txt";
  ofstream(dir + "/a/file2.txt") << "file22.txt";
  ofstream(dir + "/a/b/file3.txt") << "file33.txt";

  string targetDir = (fs::current_path() / "sandbox13").string();
  fs::create_directories(targetDir);
  fs::create_directories(targetDir + "/a/b");
  ofstream(targetDir + "/file1.txt") << "file100.txt";
  ofstream(targetDir + "/a/file2.txt") << "file200.txt";
  ofstream(targetDir + "/a/b/file3.txt") << "file300.txt";

  UFile::copyDirectoryFiles(dir, targetDir, true);
}

TEST(file, getFileObj) {
  fstream *txt = UFile::getFileObj(
      (fs::current_path() / "files_test/test_01.txt").string());
  if (txt->is_open()) {
    std::istreambuf_iterator<char> beg(*txt), end;
    string str(beg, end);
    EXPECT_EQ(str, "name\ni like code.\n");
  }
  txt->close();
}

TEST(file, moveFromFileToFileData) {
  fstream *file = new fstream;

  file->open((fs::current_path() / "files_test/fstream_test.dat").string(),
             ios::binary | ios::out | std::ios_base::app);

  string dat = (fs::current_path() / "files_test/dat_test.dat").string();

  EXPECT_TRUE(UFile::moveFromFileToFileData(file, dat));
}

#pragma endregion

#pragma region fstream

TEST(fstream, append_write) {
  int _1MB = 1024;
  char arr[1024];
  for (int i = 0; i < _1MB; ++i) {
    arr[i] = '0';
  }
  char *_1MBBuff = arr;
  ofstream file;
  file.open((fs::current_path() / "file1.dat").string(),
            ios::out | ios::binary);
  if (file.is_open()) {
    file.write((const char *)_1MBBuff, _1MB * sizeof(char));
  }
  file.close();
}

TEST(fstream, constructor) {
  fstream txt((fs::current_path() / "files_test/test_01.txt"));

  if (txt.is_open()) {
    std::istreambuf_iterator<char> beg(txt), end;
    string str(beg, end);
    EXPECT_EQ(str, "name\ni like code.\n");
  }
}

TEST(fstream, binary) {
  fstream file((fs::current_path() / "files_test/dat_test.dat"));

  if (file.is_open()) {
    file.seekg(0, ios::end);
    int length = (int)file.tellg();
    file.seekg(0, ios::beg);

    uint8_t *data = new uint8_t[length];
    file.read((char *)data, length * sizeof(char));
    EXPECT_EQ((int)data[0], 169);
  }
}

#pragma endregion
