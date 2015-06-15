#pragma once

#include "FileStorage.h"

class RamFileStorage : public FileStorage {
public:
	RamFileStorage();
	void StoreFile(string name, string read_from);
	void RetreiveFile(string name, string store_to);
	void RemoveFile(string name);
	bool HasFile(string name);
	std::vector<string> GetFileNamesList();
};