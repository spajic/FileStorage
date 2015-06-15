#include "RamFileStorage.h"

#include <fstream>

RamFileStorage::RamFileStorage() {

}

void RamFileStorage::StoreFile(string name, string read_from) {
	std::ifstream f(read_from, std::ios::binary);

	//ram_storage[name] = ;
}

bool RamFileStorage::HasFile(string name) {
	return true;
}

void RamFileStorage::RemoveFile(string name) {

}

void RamFileStorage::RetreiveFile(string name, string store_to) {

}

std::vector<string> RamFileStorage::GetFileNamesList() {
	std::vector<string> result;
	result.push_back("hello");
	return result;
}

