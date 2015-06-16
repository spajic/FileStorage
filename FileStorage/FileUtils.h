#pragma once

#include <string>
#include <vector>

namespace FileUtils {
	void ReadFileToVectorOfChars(const std::string file_name, std::vector<char> *v);
}
