#include "FileUtils.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>

namespace FileUtils {
	void ReadFileToVectorOfChars(const std::string file_name, std::vector<char> *v) {
		std::ifstream retreived_file(file_name, std::ios::binary);
		if (retreived_file.bad()) {
			return;
		}
		std::copy(
			std::istreambuf_iterator<char>(retreived_file),
			std::istreambuf_iterator<char>(),
			std::back_inserter(*v)
		);		
	}

	void WriteVectorOfCharsToFile(const std::string file_name, const std::vector<char> &v){
		std::ofstream f(file_name, std::ios::binary);
		if (!f.bad()) {
			for (auto &ch : v) {
				f << ch;
			}
		}		
	}
}