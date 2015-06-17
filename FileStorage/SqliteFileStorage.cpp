#include "SqliteFileStorage.h"

#include <fstream>
#include <vector>

#include "FileUtils.h"

#include "sqlite3.h"

SqliteFileStorage::SqliteFileStorage(std::string file_name) {
	_db_name = file_name;
	InitDatabase();
}

void SqliteFileStorage::InitDatabase() {
	OpenDatabaseConnection();
	CreateTableIfNotExists();
	PrepareInsertFileStatement();
	PrepareCheckHasFileStatement();
}

SqliteFileStorage::~SqliteFileStorage() {
	FinishWorkWithSqlite3();
}

void SqliteFileStorage::StoreFile(string name, string read_from) {
	std::vector<char> chars;
	FileUtils::ReadFileToVectorOfChars(read_from, &chars);
	BindNameToInsertFileStatement(name);
	BindFileBlobToInsertFileStatement(chars);
	ExecuteInsertFileStatement();
}

bool SqliteFileStorage::HasFile(string name) {
	BindNameToCheckHasFileStatement(name);
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

void SqliteFileStorage::PrepareInsertFileStatement() {
	string sqlInsert = 
		"INSERT INTO FileStorage (name, file) values (?, ?)";
	sqlite3_prepare_v2(
		_db, 
		sqlInsert.c_str(), // (const char*)
		sqlInsert.length(), // length of prepared SQL in BYTES
		&_insertFileStmt, // OUT: (sqlite3_stmt **) prepared stmt
		NULL // OUT: (const char**) pointer to unused portion of prepared sql string
		);
	if (_rc != SQLITE_OK) {
		throw "Can't prepare insert file statement";
	}
}

void SqliteFileStorage::BindNameToInsertFileStatement( std::string name ) {
	_rc = sqlite3_bind_text(
		_insertFileStmt, // (sqlite3_stmt*) statement to prepare
		1, // (int) number of bind parameter
		name.c_str(), // (const char*) binded text value
		name.length(), // (int) size in BYTES
		SQLITE_STATIC// ( void(*)(void*) ) destructor used to dispose text or blob
		// SQLITE_STATIC - doesn't need to be freed
		);
	if (_rc != SQLITE_OK) {
		throw "Can't bind text to insert statement";
	}
}

void SqliteFileStorage::BindFileBlobToInsertFileStatement( std::vector<char> fb ) {
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

void SqliteFileStorage::PrepareCheckHasFileStatement() {
	string sqlCheckFile = "select count(*) as n from FileStorage where name = ?";
	sqlite3_prepare_v2(
		_db, 
		sqlCheckFile.c_str(), // (const char*)
		sqlCheckFile.length(), // length of prepared SQL in BYTES
		&_checkHasFileStmt, // OUT: (sqlite3_stmt **) prepared stmt
		NULL // OUT: (const char**) pointer to unused portion of prepared sql string
		);
	if (_rc != SQLITE_OK) {
		throw "Can't prepare check has file statement";
	}
}

void SqliteFileStorage::BindNameToCheckHasFileStatement( std::string name ) {
	_rc = sqlite3_bind_text(
		_checkHasFileStmt, // (sqlite3_stmt*) statement to prepare
		1, // (int) number of bind parameter
		name.c_str(), // (const char*) binded text value
		name.length(), // (int) size in BYTES
		SQLITE_STATIC// ( void(*)(void*) ) destructor used to dispose text or blob
		// SQLITE_STATIC - doesn't need to be freed
		);
	if (_rc != SQLITE_OK) {
		throw "Can't bind name to check has file statement";
	}
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
