#include <gtest/gtest.h>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "BinFile.hpp"
#include "BmpFile.hpp"
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

#pragma region txt

TEST(txt, read_data) {
  TxtFile test_01(fs::current_path() / "test_files/test_01.txt");

  EXPECT_TRUE(test_01.readData());
  EXPECT_EQ(test_01.getData(), "name\ni like code.\n");
}

TEST(txt, write_data) {
  TxtFile test_02(fs::current_path() / "test_files/test_02.txt");

  test_02.setData("hei\nare you ok?\n");

  EXPECT_TRUE(test_02.writeData());
  EXPECT_TRUE(test_02.readData());
  EXPECT_EQ(test_02.getData(), "hei\nare you ok?\n");
}

TEST(txt, append_write_data) {
  TxtFile test_03(fs::current_path() / "test_files/test_03.txt");

  test_03.setData("hello!\n");

  EXPECT_TRUE(test_03.writeData());
  EXPECT_TRUE(test_03.appendWriteData("hello!\n"));
  EXPECT_TRUE(test_03.readData());
  EXPECT_EQ(test_03.getData(), "hello!\nhello!\n");
}

#pragma endregion

#pragma region ini

TEST(ini, ini_setup) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());
}

TEST(ini, get_string) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  string value_01;
  string value_02;
  string value_03;

  string section = "string";
  string key = "str2";

  test_01.getFromIni("string", "str1", value_01, "qi");
  test_01.getFromIni(section, key, value_02, "tian");
  test_01.getFromIni("string", "str3", value_03, "fun");

  EXPECT_EQ(value_01, "name");
  EXPECT_EQ(value_02, "hello");
  EXPECT_EQ(value_03, "fun");
}

TEST(ini, get_int) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  int value_01;
  int value_02;
  int value_03;

  string section = "int";
  string key = "int2";

  test_01.getFromIni("int", "int1", value_01, 19);
  test_01.getFromIni(section, key, value_02, 19);
  test_01.getFromIni("int", "int3", value_03, 19);

  EXPECT_EQ(value_01, 11);
  EXPECT_EQ(value_02, 8);
  EXPECT_EQ(value_03, 19);
}

TEST(ini, get_float) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  float value_01;
  float value_02;
  float value_03;

  string section = "float";
  string key = "float2";

  test_01.getFromIni("float", "float1", value_01, 22.09f);
  test_01.getFromIni(section, key, value_02, 22.09f);
  test_01.getFromIni("float", "float3", value_03, 22.09f);

  EXPECT_FLOAT_EQ(value_01, 33.33f);
  EXPECT_FLOAT_EQ(value_02, 22.22f);
  EXPECT_FLOAT_EQ(value_03, 22.09f);
}

TEST(ini, get_double) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  double value_01;
  double value_02;
  double value_03;

  string section = "double";
  string key = "double2";

  test_01.getFromIni("double", "double1", value_01, 19.09);
  test_01.getFromIni(section, key, value_02, 19.09);
  test_01.getFromIni("double", "double3", value_03, 19.09);

  EXPECT_DOUBLE_EQ(value_01, 3.14);
  EXPECT_DOUBLE_EQ(value_02, 1.01);
  EXPECT_DOUBLE_EQ(value_03, 19.09);
}

TEST(ini, get_bool) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  bool value_01;
  bool value_02;
  bool value_03;

  string section = "bool";
  string key = "bool2";

  test_01.getFromIni("bool", "bool1", value_01, false);
  test_01.getFromIni(section, key, value_02, false);
  test_01.getFromIni("bool", "bool3", value_03, true);

  EXPECT_EQ(value_01, true);
  EXPECT_EQ(value_02, false);
  EXPECT_EQ(value_03, true);
}

TEST(ini, get_array_int) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  int array[8];
  int test_array[] = {81, 71, 61, 51, 41, 31, 21, 11};
  int test_default_array[8];
  int default_array[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = 8;

  test_01.getFromIni("array", "arrayInt", array, default_array, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array[i], test_array[i]);
  }

  test_01.getFromIni("array", "arrayInt_testD", test_default_array,
                     default_array, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(test_default_array[i], default_array[i]);
  }
}

TEST(ini, get_array_float) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  float array[5];
  float test_array[] = {1.1f, 2.1f, 3.1f, 4.1f, 5.1f};
  float test_default_array[5];
  float default_array[] = {1.11f, 2.11f, 3.11f, 4.11f, 5.11f};
  int size = 5;

  test_01.getFromIni("array", "arrayFloat", array, default_array, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_FLOAT_EQ(array[i], test_array[i]);
  }

  test_01.getFromIni("array", "arrayFloat_testD", test_default_array,
                     default_array, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_FLOAT_EQ(test_default_array[i], default_array[i]);
  }
}

TEST(ini, get_array_double) {
  IniFile test_01(fs::current_path() / "test_files/test_01.ini");

  EXPECT_TRUE(test_01.setup());

  double array[5];
  double test_array[] = {1.01, 2.01, 3.01, 4.01, 5.01};
  double test_default_array[5];
  double default_array[] = {1.11, 2.11, 3.11, 4.11, 5.11};
  int size = 5;

  test_01.getFromIni("array", "arrayDouble", array, default_array, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_DOUBLE_EQ(array[i], test_array[i]);
  }

  test_01.getFromIni("array", "arrayDouble_testD", test_default_array,
                     default_array, size);
  for (int i = 0; i < size; ++i) {
    EXPECT_DOUBLE_EQ(test_default_array[i], default_array[i]);
  }
}

TEST(ini, get_false_case) {
  IniFile test_03(fs::current_path() / "test_files/no_find.ini");

  EXPECT_FALSE(test_03.setup());

  int value_01;
  int value_02;

  test_03.getFromIni("int", "int1", value_01, 22);
  test_03.getFromIni("int", "int2", value_02, 22);

  EXPECT_EQ(value_01, 22);
  EXPECT_EQ(value_02, 22);
}

TEST(ini, set_data) {
  IniFile test_02(fs::current_path() / "test_files/test_02.ini");

  if (test_02.setup()) {
    test_02.setToIni("string", "str1", "name");
    test_02.setToIni("int", "int1", 22);
    test_02.setToIni("float", "float1", 22.09f);
    test_02.setToIni("double", "double1", 22.09);
    test_02.setToIni("bool", "bool1", true);

    test_02.save();
  }
}

TEST(ini, set_array_data) {
  IniFile test_02(fs::current_path() / "test_files/test_02.ini");

  if (test_02.setup()) {
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

#pragma region json

TEST(json, json_setup) {
  JsonFile test(fs::current_path() / "test_files/test.json");

  EXPECT_TRUE(test.setup());
}

TEST(json, get_data) {
  JsonFile test(fs::current_path() / "test_files/test.json");

  string json_value_string;
  int json_value_int;
  double json_value_double;
  bool json_value_bool;
  int depth_json_value_int;
  bool depth_json_value_bool;
  string depth_json_value_string;

  EXPECT_TRUE(test.setup());

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
  JsonFile test(fs::current_path() / "test_files/test.json");

  string json_value[3];
  string json_target_value[] = {"python", "c++", "ruby"};
  string json_default_value[] = {"java", "c#", "php"};
  int size = 3;

  EXPECT_TRUE(test.setup());
  test.getFromJson("plug-ins", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_int_data) {
  JsonFile test(fs::current_path() / "test_files/test.json");

  int json_value[3];
  int json_target_value[] = {1, 2, 3};
  int json_default_value[] = {3, 2, 1};
  int size = 3;

  EXPECT_TRUE(test.setup());
  test.getFromJson("indent.int_arr", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_array_double_data) {
  JsonFile test(fs::current_path() / "test_files/test.json");

  double json_value[3];
  double json_target_value[] = {1.11, 2.11, 3.11};
  double json_default_value[] = {3.11, 2.11, 1.11};
  int size = 3;

  EXPECT_TRUE(test.setup());
  test.getFromJson("indent.double_arr", json_value, json_default_value, size);

  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(json_value[i], json_target_value[i]);
  }
}

TEST(json, get_data_from_Json_false_case) {
  JsonFile test(fs::current_path() / "test_files/json_false.json");

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

  EXPECT_FALSE(test.setup());

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
  JsonFile store_json(fs::current_path() / "test_files/store_json.json");

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

#pragma region dat

TEST(dat, read_data) {
  BinFile test(fs::current_path() / "test_files/test.dat");

  EXPECT_TRUE(test.readData());
  EXPECT_EQ(test.getData().size(), 8192);
  EXPECT_EQ(test.getData()[0], 169);
}

TEST(dat, write_data) {
  BinFile test(fs::current_path() / "test_files/test.dat");

  if (test.readData()) {
    BinFile dat_test_copy(fs::current_path() / "test_files/dat_test_copy.dat");

    dat_test_copy.setData(test.getData());

    EXPECT_TRUE(dat_test_copy.writeData());
    EXPECT_EQ(dat_test_copy.getData().size(), 8192);
    EXPECT_EQ(dat_test_copy.getData()[0], 169);
  }
}

TEST(dat, append_write_data) {
  BinFile test(fs::current_path() / "test_files/test.dat");

  if (test.readData()) {
    BinFile dat_test_append(fs::current_path() /
                            "test_files/dat_test_append.dat");

    dat_test_append.setData(test.getData());

    EXPECT_TRUE(dat_test_append.writeData());
    EXPECT_EQ(dat_test_append.getData().size(), 8192);
    EXPECT_EQ(dat_test_append.getData()[0], 169);

    dat_test_append.appendWriteData(test.getData());

    EXPECT_TRUE(dat_test_append.writeData());
    EXPECT_EQ(dat_test_append.getData().size(), 16384);
    EXPECT_EQ(dat_test_append.getData()[8192], 169);
  }
}

#pragma endregion

#pragma region bmp

TEST(bmp, read_data) {
  BmpFile test_01(fs::current_path() / "test_files/test_01.bmp");
  BmpFile test_02(fs::current_path() / "test_files/test_02.bmp");

  BMP bmpObject_01(test_01.path().c_str());
  BMP bmpObject_02(test_02.path().c_str());

  EXPECT_EQ(bmpObject_01.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_01.bmp_info_header.width, 128);
  EXPECT_EQ(bmpObject_02.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_02.bmp_info_header.width, 16);
}

TEST(bmp, copy_bmp) {
  BmpFile test_01(fs::current_path() / "test_files/test_01.bmp");

  string copy_bmp_file =
      (fs::current_path() / "test_files/copy_bmp.bmp").string();

  BMP bmpObject(test_01.path().c_str());
  bmpObject.write(copy_bmp_file.c_str());

  BMP bmpObject_copy(copy_bmp_file.c_str());
  EXPECT_EQ(bmpObject_copy.bmp_info_header.height, 256);
  EXPECT_EQ(bmpObject_copy.bmp_info_header.width, 128);
}

#pragma endregion

#pragma region img

TEST(img, read_data) {
  string img_p = (fs::current_path() / "test_files/rocket.jpg").string();

  BinFile file(img_p);

  EXPECT_TRUE(file.readData());
  EXPECT_EQ(file.getLength(), 1281491);
}

TEST(img, write_data) {
  BinFile file(fs::current_path() / "test_files/rocket.jpg");

  if (file.readData()) {
    BinFile copy_f(fs::current_path() / "test_files/rocket_copy.jpg");
    copy_f.setData(file.getData());
    copy_f.setLength(file.getLength());

    EXPECT_TRUE(copy_f.writeData());
    EXPECT_EQ(fs::exists(copy_f.path()), true);
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
  vec = {true, 'c', 1, 1.2, "hello", "true"};

  EXPECT_EQ(vec[0].toString(), "true");
  EXPECT_EQ(vec[1].toString(), "c");
  EXPECT_EQ(vec[2].toString(), "1");
  EXPECT_EQ(vec[3].toString(), "1.2");
  EXPECT_EQ(vec[4].toString(), "hello");
  EXPECT_EQ(vec[5].toBool(), true);
}
#pragma endregion

#pragma region file

TEST(file, exist) {
  fs::path path_01 = fs::current_path() / "test_files/test_01.txt";
  fs::path path_02 = fs::current_path() / "test_files/test_10.txt";

  EXPECT_TRUE(fs::exists(UFile(path_01).path()));
  EXPECT_FALSE(fs::exists(UFile(path_02).path()));
}

TEST(file, get_file_size) {
  fs::path p = fs::current_path() / "example.bin";
  UFile file = UFile(p);

  ofstream(p) << "hello world";  // create file of size 1

  EXPECT_EQ(fs::file_size(file.path()), 11);

  fs::remove(p);
}

TEST(file, get_absolute_path) {
  fs::path p = fs::current_path() / "test.txt";
  UFile file = UFile(p);

  ofstream(p) << "hello world";  // create file of size 11

  EXPECT_EQ(fs::absolute(file.path()), p);
}

TEST(file, delete_file) {
  fs::path p = fs::current_path() / "hello.cpp";
  UFile file = UFile(p);

  ofstream(p) << "world";

  EXPECT_EQ(fs::file_size(file.path()), 5);

  EXPECT_TRUE(fs::remove(p));
}

TEST(file, delete_directory) {
  fs::create_directories(fs::current_path() / "test_files/hello_d");

  fs::path test_d = fs::current_path() / "test_files/hello_d/test_d";
  ofstream(test_d) << "test_d";
  fs::path test_d_md = fs::current_path() / "test_files/hello_d/test_d.md";
  ofstream(test_d_md) << "test_d";
  fs::path test_d_txt = fs::current_path() / "test_files/hello_d/test_d.txt";
  ofstream(test_d_txt) << "test_d";

  fs::path d = (fs::current_path() / "test_files/hello_d");

  EXPECT_NE(fs::remove_all(d), 0);
}

TEST(file, if_file_exist_then_find_its_father_directory) {
  string path = (fs::current_path() / "test_files/test_01.txt").string();
  if (fs::exists(path)) {
    EXPECT_EQ(fs::path(path).parent_path(),
              (fs::current_path() / "test_files").string());
  }
}

TEST(file, false_to_find_its_father_directory_and_then_create_it) {
  string txt = (fs::current_path() / "files_txt/test_01.txt").string();

  fs::remove_all(fs::path(txt).parent_path());

  if (!fs::exists(fs::path(txt).parent_path())) {
    fs::create_directory(fs::path(txt).parent_path());

    EXPECT_EQ(fs::path(txt).parent_path(),
              (fs::current_path() / "files_txt").string());
  }
}

TEST(file, copy) {
  const auto copyOptions =
      fs::copy_options::update_existing | fs::copy_options::recursive;

  string txt_path = (fs::current_path() / "test_files/test_01.txt").string();
  string copy_txt_path =
      (fs::current_path() / "test_files/copy_test_01.txt").string();

  fs::copy(txt_path, copy_txt_path, copyOptions);

  EXPECT_EQ(fs::file_size(copy_txt_path), 18);

  string ini_path = (fs::current_path() / "test_files/test_01.ini").string();
  string copy_ini_path =
      (fs::current_path() / "test_files/copy_test_01.ini").string();

  fs::copy(ini_path, copy_ini_path, copyOptions);

  EXPECT_EQ(fs::file_size(copy_ini_path), 306);

  string json_path = (fs::current_path() / "test_files/test.json").string();
  string copy_json_path =
      (fs::current_path() / "test_files/copy_test.json").string();

  fs::copy(json_path, copy_json_path, copyOptions);

  EXPECT_EQ(fs::file_size(copy_json_path), 256);

  string dat_path = (fs::current_path() / "test_files/test.dat").string();
  string copy_dat_path =
      (fs::current_path() / "test_files/copy_test.dat").string();

  fs::copy(dat_path, copy_dat_path, copyOptions);

  EXPECT_EQ(fs::file_size(copy_dat_path), 8192);

  string bmp_path = (fs::current_path() / "test_files/test_01.bmp").string();
  string copy_bmp_path =
      (fs::current_path() / "test_files/copy_test_01.bmp").string();

  fs::copy(bmp_path, copy_bmp_path, copyOptions);

  EXPECT_EQ(fs::file_size(copy_bmp_path), 98358);
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
  fstream txt((fs::current_path() / "test_files/test_01.txt"));

  if (txt.is_open()) {
    std::istreambuf_iterator<char> beg(txt), end;
    string str(beg, end);
    EXPECT_EQ(str, "name\ni like code.\n");
  }
}

TEST(fstream, binary) {
  fstream file((fs::current_path() / "test_files/test.dat"));

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

#pragma region tools

TEST(tools, split) {
  vector<string> a = split("a", ".");
  vector<string> b = split("a.b.c", ".");
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(b.size(), 3);
}

#pragma endregion
