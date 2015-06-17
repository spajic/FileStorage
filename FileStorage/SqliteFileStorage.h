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

	void InitDatabase();
	void OpenDatabaseConnection();
	void CreateTableIfNotExists();

	void PrepareInsertFileStatement();
	void BindNameToInsertFileStatement(const std::string &name);
	void BindFileBlobToInsertFileStatement(const std::vector<char> &fb);
	void ExecuteInsertFileStatement();

	void PrepareDeleteFileStatement();
	void BindNameToDeleteFileStatement(const std::string &name);
	void ExecuteDeleteFileStatement();

	void PrepareSelectFileStatement();
	void BindNameToSelectFileStatement(const std::string &name);
	void ExecuteSelectFileStatement();

	void PrepareCheckHasFileStatement();
	void BindNameToCheckHasFileStatement(const std::string &name);
	bool ExecuteCheckHasFileStatement();

	void FinishWorkWithSqlite3();
};