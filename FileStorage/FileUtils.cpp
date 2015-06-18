#include "FileUtils.h"

#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <memory>

namespace FileUtils {

TempFile::TempFile(std::string file_name, std::vector<char> chars) {
	_filename = file_name;
	WriteVectorOfCharsToFile(file_name, chars);
}

TempFile::~TempFile() {
	if(remove(_filename.c_str()) != 0) {
		throw std::exception(("Can't remove file: " + _filename).c_str());
	}
}

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
	if (f.bad()) {
		throw std::exception(("Can't open file: " + file_name).c_str());
	}
	for (auto &ch : v) { 
		f << ch;
	}		
}

} // end namespace FileUtils 