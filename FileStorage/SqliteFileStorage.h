#pragma once

#include "FileStorage.h"

#include <map>
#include <vector>

#include "sqlite3.h"

class SqliteFileStorage : public FileStorage {
public:
	SqliteFileStorage();
	~SqliteFileStorage();
	void StoreFile(string name, string read_from);
	void RetreiveFile(string name, string store_to);
	void RemoveFile(string name);
	bool HasFile(string name);
	std::vector<string> GetFileNamesList();
	void InitDatabase(std::string file_name);
private:
	sqlite3 *db;
	std::string db_name;
};