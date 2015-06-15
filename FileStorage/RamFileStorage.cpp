#include "RamFileStorage.h"

RamFileStorage::RamFileStorage() {

}

void RamFileStorage::StoreFile(string name, string read_from) {

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

