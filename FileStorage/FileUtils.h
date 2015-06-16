#pragma once

#include <string>
#include <vector>

namespace FileUtils {
	void ReadFileToVectorOfChars(const std::string file_name, std::vector<char> *v);
	void WriteVectorOfCharsToFile(const std::string file_name, const std::vector<char> &v);
}
