#include "Convertor.h"

using std::string;
using std::vector;

int main(int argc, char* argv[])
{
	if (argc == 2 && (strcmp(argv[1], "-h") == 0))
	{
		std::cout << "-t [Texture] [From Encoding] [To Encoding]\t\tConvert input texture\n";
		std::cout << "-f [FilePath|FileName] [From Encoding] [To Encoding]\tConvert input file content\n";
		std::cout << "-h help\n";
		std::cout << "Encoding:\n\tUTF-8:\t\t\"UTF-8\"\n\tGBK:\t\t\"GBK\"\n\tBig5:\t\t\"BIG5\"\n\tShift-JIS:\t\"SHIFT-JIS\"\n\tLatin-1:\t\"ISO-8859-1\"";
		std::cout << "Refer to the documentation of the libiconv library for more encoding\n"
		return 0;
	}
	if (argc <= 4) { std::cout << "ERROR:Insufficient Parameters\nUse \"-h\" to get help"; return 0; }

	Convertor convertor;
	std::cout << argv[2] << " " << argv[3] << " " << argv[4] << std::endl;
	if (strcmp(argv[1], "-t") == 0)
	{
		convertor.doConvert_t(argv[2], argv[3], argv[4]);
	}

	if (strcmp(argv[1], "-f") == 0)
	{
		string input_str = convertor.inputTextfile(argv[2]);
		if (input_str == "error") { return 0; }
		string output_str = convertor.doConvert_t(input_str, argv[3], argv[4]);
		convertor.outputTextfile(output_str);
	}
}