#include "RamFileStorage.h"

#include <fstream>
#include <vector>

#include "FileUtils.h"

RamFileStorage::RamFileStorage() {

}

void RamFileStorage::StoreFile(string name, string read_from) {
	std::vector<char> chars;
	FileUtils::ReadFileToVectorOfChars(read_from, &chars);
	ram_storage[name] = chars;
}

bool RamFileStorage::HasFile(string name) {
	return (ram_storage.count(name) == 1);
}

void RamFileStorage::RemoveFile(string name) {
	ram_storage.erase(name);
}

void RamFileStorage::RetreiveFile(string name, string store_to) {
	FileUtils::WriteVectorOfCharsToFile(store_to, ram_storage[name]);
}

std::vector<string> RamFileStorage::GetFileNamesList() {
	std::vector<string> result;
	for (auto &elem : ram_storage) {
		result.push_back(elem.first);
	}
	return result;
}

