#pragma once

#include <string>
#include <vector>
#include <map>

#include "sqlite3.h"

class SqliteTestDB1Generator {
public:
		bool GenerateTestDB1(std::string db_name);
private:
	void CheckDbFileNotExists();
	void OpenDatabase();
	void CreateTable();
	void PrepareInsertStatement();
	void GenerateDataToInsert();
	void InsertDataIntoTable();
	void BindTextToInsertStatement(const std::string &name);
	void BindBlobToInsertStatement(const std::vector<char> &b);
	void ExecuteInsertStatement();
	void FinalizeWorkWithSqlite3();

	std::map<std::string, std::vector<char> > _dataToInsert;

	std::string _db_name;
	sqlite3* _db;
	sqlite3_stmt *_preparedInsert;
	int _rc;
	char* _error;
};
