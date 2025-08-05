#pragma once
#include <iostream>
#include <iconv.h>
#include <string>
#include <cerrno>
#include <vector>
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

class Convertor
{
public:
	string convert_encoding(const string& input, const string& from_encoding, const string& to_encoding);	//编码格式转换方法
	string doConvert_t(string input_str, string from_encoding, string to_encoding);
	string inputTextfile(string input_filepath);
	void outputTextfile(string output_str);
};

