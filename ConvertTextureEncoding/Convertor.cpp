#include "Convertor.h"

string Convertor::convert_encoding(const string& input, const string& from_encoding, const string& to_encoding)
{
	iconv_t cd = iconv_open(to_encoding.c_str(), from_encoding.c_str());
	if (cd == (iconv_t)-1)	//抛出runtime_error异常
	{
		throw std::runtime_error("Failed to open iconv descriptor");
	}

	//输入缓冲
	size_t in_bytes_left = input.size();
	char* in_buf = const_cast<char*>(input.data());

	//输出缓冲 稍大于输入缓冲
	size_t out_bytes_left = input.size() * 4 + 1;	//设置安全边界
	vector<char> out_buf(out_bytes_left);
	char* out_ptr = out_buf.data();

	size_t result = iconv(cd, &in_buf, &in_bytes_left, &out_ptr, &out_bytes_left);
	iconv_close(cd);	//关闭iconv

	//错误检查
	if (result == (size_t)-1)
	{
		string err = "Convertion failed:";
		switch (errno)
		{
		case EILSEQ:
			err += "Invalid input sequence";
			break;
		case E2BIG:
			err += "Output buffer too small";
			break;
		case EINVAL:
			err += "Incomplete input sequence";
			break;
		default:
			err += "Unknown error";
		}
		throw std::runtime_error(err);
	}

	//返回有效内容
	return string(out_buf.data(), out_ptr - out_buf.data());
}

string Convertor::doConvert_t(string input_str, string from_encoding, string to_encoding)
{
	try
	{
		string output_str = convert_encoding(input_str, from_encoding, to_encoding);
		std::cout << "Converted " << output_str.size() << "bytes\n";

		if (to_encoding == "UTF-8") { system("chcp 65001>nul"); }
		if (to_encoding == "GBK") { system("chcp 936>nul"); }
		if (to_encoding == "BIG5") { system("chcp 950>nul"); }
		if (to_encoding == "SHIFT-JIS") { system("chcp 932>nul"); }
		if (to_encoding == "ISO-8859-1") { system("chcp 28591>nul"); }

		std::cout << output_str;

		return output_str;
	}
	catch (const std::exception& err)
	{
		std::cerr << "Error:" << err.what() << std::endl;
		return "error";
	}
}

//使用rdbuf输入到字符串流
string Convertor::inputTextfile(string input_filepath)
{
	std::ifstream from_text;
	from_text.open(input_filepath, std::ios::in);
	if (!from_text.is_open())
	{
		throw std::runtime_error("Failed to open file:" + input_filepath);	//打开文件失败 抛出异常
		return "error";
	}
	std::stringstream input_buf;
	input_buf << from_text.rdbuf();
	from_text.close();
	return input_buf.str();
}

void Convertor::outputTextfile(string output_str)
{
	std::ofstream to_text;
	to_text.open("output.txt", std::ios::out | std::ios::trunc);
	to_text << output_str;
	to_text.close();
}
