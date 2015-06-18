#pragma once

#include "FileStorage.h"

#include <map>
#include <vector>

#include "sqlite3.h"

class SqliteFileStorage : public FileStorage {
public:
	SqliteFileStorage(std::string file_name);
	~SqliteFileStorage();
	void StoreFile(string name, string read_from);
	void RetreiveFile(string name, string store_to);
	void RemoveFile(string name);
	bool HasFile(string name);
	std::vector<string> GetFileNamesList();
	
	
private:
	sqlite3 *_db;
	std::string _db_name;
	int _rc;
	char *_error;

	sqlite3_stmt *_insertFileStmt;
	sqlite3_stmt *_checkHasFileStmt;
	sqlite3_stmt *_deleteFileStmt;

	void InitDatabase();
	void OpenDatabaseConnection();
	void CreateTableIfNotExists();

	void BindFileBlobToInsertFileStatement(const std::vector<char> &fb);
	void ExecuteInsertFileStatement();

	void ExecuteDeleteFileStatement();

	void ExecuteSelectFileStatement();

	bool ExecuteCheckHasFileStatement();

	void FinishWorkWithSqlite3();
};