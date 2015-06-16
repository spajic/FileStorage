#pragma once

#include "FileStorage.h"

#include <map>
#include <vector>

class SqliteFileStorage : public FileStorage {
public:
	SqliteFileStorage();
	void StoreFile(string name, string read_from);
	void RetreiveFile(string name, string store_to);
	void RemoveFile(string name);
	bool HasFile(string name);
	std::vector<string> GetFileNamesList();
private:
};