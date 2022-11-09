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

TEST(iniFile_Test, getStringFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  std::string str_value_01;
  std::string str_value_02;
  std::string str_value_03;

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "string", "str1", str_value_01, "qi"),
      true);
  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "string", "str2", str_value_02, "qi"),
      true);
  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "string", "str3", str_value_03, "qi"),
      true);
  EXPECT_EQ(str_value_01, "kok-s0s");
  EXPECT_EQ(str_value_02, "hello");
  EXPECT_EQ(str_value_03, "qi");
}

TEST(iniFile_Test, getIntFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  int int_value_01;
  int int_value_02;
  int int_value_03;

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "int", "int1", int_value_01, 19),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "int", "int2", int_value_02, 19),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "int", "int3", int_value_03, 19),
            true);
  EXPECT_EQ(int_value_01, 11);
  EXPECT_EQ(int_value_02, 8);
  EXPECT_EQ(int_value_03, 19);
}

TEST(iniFile_Test, getFloatFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  float float_value_01;
  float float_value_02;
  float float_value_03;

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "float", "float1", float_value_01,
                                 22.09f),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "float", "float2", float_value_02,
                                 22.09f),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "float", "float3", float_value_03,
                                 22.09f),
            true);
  EXPECT_EQ(float_value_01, 33.33f);
  EXPECT_EQ(float_value_02, 22.22f);
  EXPECT_EQ(float_value_03, 22.09f);
}

TEST(iniFile_Test, getDoubleFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  double double_value_01;
  double double_value_02;
  double double_value_03;

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "double", "double1",
                                 double_value_01, 19.09),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "double", "double2",
                                 double_value_02, 19.09),
            true);
  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "double", "double3",
                                 double_value_03, 19.09),
            true);
  EXPECT_EQ(double_value_01, 3.14);
  EXPECT_EQ(double_value_02, 1.01);
  EXPECT_EQ(double_value_03, 19.09);
}

TEST(iniFile_Test, getBoolFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  bool bool_value_01;
  bool bool_value_02;
  bool bool_value_03;

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "bool", "bool1", bool_value_01, false),
      true);
  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "bool", "bool2", bool_value_02, true),
      true);
  EXPECT_EQ(
      fileTools.getFromIni(ini_test_01, "bool", "bool3", bool_value_03, true),
      true);
  EXPECT_EQ(bool_value_01, true);
  EXPECT_EQ(bool_value_02, false);
  EXPECT_EQ(bool_value_03, true);
}

TEST(iniFile_Test, getArrayIntFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  int array_int[8];
  int array_int_testD[8];
  int default_array_int[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int size = 8;
  int right_array_int[] = {81, 71, 61, 51, 41, 31, 21, 11};

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayInt", array_int,
                                 default_array_int, size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int[i], right_array_int[i]);
  }

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayInt_testD",
                                 array_int_testD, default_array_int, size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_int_testD[i], default_array_int[i]);
  }
}

TEST(iniFile_Test, getArrayFloatFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  float array_float[5];
  float array_float_testD[5];
  float default_array_float[] = {1.11f, 2.11f, 3.11f, 4.11f, 5.11f};
  int size = 5;
  float right_array_float[] = {1.1f, 2.1f, 3.1f, 4.1f, 5.1f};

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayFloat",
                                 array_float, default_array_float, size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_float[i], right_array_float[i]);
  }

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayFloat_testD",
                                 array_float_testD, default_array_float, size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_float_testD[i], default_array_float[i]);
  }
}

TEST(iniFile_Test, getArrayDoubleFromIni) {
  IniFile ini_test_01;
  ini_test_01.path =
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini";
  double array_double[5];
  double array_double_testD[5];
  double default_array_double[] = {1.11, 2.11, 3.11, 4.11, 5.11};
  int size = 5;
  double right_array_double[] = {1.01, 2.01, 3.01, 4.01, 5.01};

  EXPECT_EQ(
      ini_test_01.path,
      "D:\\work\\mobile_Ocean\\cxx_crud_file\\files_test\\ini_test_01.ini");

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayDouble",
                                 array_double, default_array_double, size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_double[i], right_array_double[i]);
  }

  EXPECT_EQ(fileTools.getFromIni(ini_test_01, "array", "arrayDouble_testD",
                                 array_double_testD, default_array_double,
                                 size),
            true);
  for (int i = 0; i < size; ++i) {
    EXPECT_EQ(array_double_testD[i], default_array_double[i]);
  }
}