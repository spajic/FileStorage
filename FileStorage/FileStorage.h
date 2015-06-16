#pragma once

#include <string>
#include <vector>

using std::string;

class FileStorage {
public:
	virtual ~FileStorage() {}
	virtual void StoreFile(string name, string read_from) = 0;
	virtual void RetreiveFile(string name, string store_to) = 0;
	virtual void RemoveFile(string name) = 0;
	virtual bool HasFile(string name) = 0;
	virtual std::vector<string> GetFileNamesList() = 0;
};
