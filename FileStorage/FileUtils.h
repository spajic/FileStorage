#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>

namespace FileUtils {

void ReadFileToVectorOfChars(const std::string file_name, std::vector<char> *v);
void WriteVectorOfCharsToFile(const std::string file_name, const std::vector<char> &v);

class TempFile {
public:
	TempFile(std::string file_name, std::vector<char> chars);
	~TempFile();
private:
	std::string _filename;
};

} // end FileUtils namespace
