#include "SqliteFileStorage.h"

#include <fstream>
#include <vector>

#include "FileUtils.h"

SqliteFileStorage::SqliteFileStorage() {

}

void SqliteFileStorage::StoreFile(string name, string read_from) {
	std::vector<char> chars;
	FileUtils::ReadFileToVectorOfChars(read_from, &chars);
}

bool SqliteFileStorage::HasFile(string name) {
	return true;
}

void SqliteFileStorage::RemoveFile(string name) {

}

void SqliteFileStorage::RetreiveFile(string name, string store_to) {
	
}

std::vector<string> SqliteFileStorage::GetFileNamesList() {
	std::vector<string> result;
	result.push_back("hello from sqilte stub");
	return result;
}

