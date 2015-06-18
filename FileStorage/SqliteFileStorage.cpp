#include "SqliteFileStorage.h"

#include <fstream>
#include <vector>

#include "FileUtils.h"
#include "SqliteUtils.h"

#include "sqlite3.h"

using SqliteUtils::PrepareStatment;
using SqliteUtils::BindString;

SqliteFileStorage::SqliteFileStorage(std::string file_name) {
	_db_name = file_name;
	InitDatabase();
}

void SqliteFileStorage::InitDatabase() {
	OpenDatabaseConnection();
	CreateTableIfNotExists();
	PrepareStatment(_db, &_insertFileStmt, "INSERT INTO FileStorage (name, file) values (?, ?)");
	PrepareStatment(_db, &_checkHasFileStmt, "select count(*) as n from FileStorage where name = ?");
	PrepareStatment(_db, &_deleteFileStmt, "delete from FileStorage where name = ?");
}

SqliteFileStorage::~SqliteFileStorage() {
	FinishWorkWithSqlite3();
}

void SqliteFileStorage::StoreFile(string name, string read_from) {
	std::vector<char> chars;
	FileUtils::ReadFileToVectorOfChars(read_from, &chars);
	BindString(_insertFileStmt, 1, name);
	BindFileBlobToInsertFileStatement(chars);
	ExecuteInsertFileStatement();
}

bool SqliteFileStorage::HasFile(string name) {
	BindString(_checkHasFileStmt, 1, name);
	return ExecuteCheckHasFileStatement();
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

// --------------------------- private part ------------------------------------------
void SqliteFileStorage::OpenDatabaseConnection() {
	_rc = sqlite3_open(_db_name.c_str(), &_db);
	if(_rc) {
		throw "Can't open database";
	}
}

void SqliteFileStorage::CreateTableIfNotExists() {
	const string sqlCreateTable = 
		"create table if not exists FileStorage (name TEXT PRIMARY KEY, file BLOB);";
	_rc = sqlite3_exec(_db, sqlCreateTable.c_str(), NULL, NULL, &_error);
	if(_rc) {
		throw "Can't create table";
	}
}

void SqliteFileStorage::FinishWorkWithSqlite3() {
	sqlite3_close(_db);
}

void SqliteFileStorage::BindFileBlobToInsertFileStatement(const std::vector<char> &fb ) {
	_rc = sqlite3_bind_blob(
		_insertFileStmt, 
		2, 
		fb.data(), 
		fb.size(), 
		SQLITE_STATIC
		);
	if(_rc != SQLITE_OK) {
		throw "Can't bind blob to insert statement";
	}
}

void SqliteFileStorage::ExecuteInsertFileStatement() {
	_rc = sqlite3_step(_insertFileStmt);
	if(_rc != SQLITE_DONE) {
		throw "Can't execute prepared insert statement";
	}
	sqlite3_reset(_insertFileStmt);
}

bool SqliteFileStorage::ExecuteCheckHasFileStatement() {
	_rc = sqlite3_step(_checkHasFileStmt);
	if(_rc != SQLITE_ROW) {
  		throw "Can't execute prepared check has file statement";
	}
	int n = sqlite3_column_int(_checkHasFileStmt, 0);
	sqlite3_reset(_checkHasFileStmt);
	return (n > 0);
}
