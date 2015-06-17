#include "SqliteUtils.h"

#include <cstdio>
#include <fstream>
#include <vector>
#include "sqlite3.h"

using std::string;

/* Генерация базы данных для тестирования.
Возвращает true, если БД сгенерирована успешно, иначе false.
БД создаётся заново в файле db_name. 
БД содержит одну таблицу: FileStorage(name TEXT PRIMARY KEY, file BLOB)
Таблица FileStorage содержит 3 строки:
 - (File 1, 111)
 - (File 2, 222222)
 - (File 3, 333333333)
*/
bool SqliteTestDB1Generator::GenerateTestDB1(std::string db_name) {
	_db_name = db_name;
	GenerateDataToInsert();
	CheckDbFileNotExists();
	
	OpenDatabase();
	CreateTable();
	PrepareInsertStatement();
	InsertDataIntoTable();
	FinalizeWorkWithSqlite3();
	return true;
}

void SqliteTestDB1Generator::CheckDbFileNotExists() {
	if(std::ifstream(_db_name)) {
		if(remove(_db_name.c_str()) != 0) {
			throw "Can't remove db file";
		}
	}
}

void SqliteTestDB1Generator::OpenDatabase() {
	_rc = sqlite3_open(_db_name.c_str(), &_db);
	if(_rc) {
		throw "Can't open database";
	}
}

void SqliteTestDB1Generator::CreateTable() {
	string sqlCreateTable = 
		"CREATE TABLE FileStorage (name TEXT PRIMARY KEY, file BLOB);";
	_rc = sqlite3_exec(_db, sqlCreateTable.c_str(), NULL, NULL, &_error);
	if(_rc) {
		throw "Can't create table";
	}
}

void SqliteTestDB1Generator::PrepareInsertStatement() {
	string sqlInsert = 
		"INSERT INTO FileStorage (name, file) values (?, ?)";
	sqlite3_prepare_v2(
		_db, 
		sqlInsert.c_str(), // (const char*)
		sqlInsert.length(), // length of prepared SQL in BYTES
		&_preparedInsert, // OUT: (sqlite3_stmt **) prepared stmt
		NULL // OUT: (const char**) pointer to unused portion of prepared sql string
		);
	if (_rc != SQLITE_OK) {
		throw "Can't prepare insert statement";
	}
}

void SqliteTestDB1Generator::InsertDataIntoTable() {
	for(auto &d : _dataToInsert) {
		BindTextToInsertStatement(d.first);
		BindBlobToInsertStatement(d.second);
		ExecuteInesrtStatement();
	}
}

void SqliteTestDB1Generator::BindTextToInsertStatement(std::string name) {
	_rc = sqlite3_bind_text(
		_preparedInsert, // (sqlite3_stmt*) statement to prepare
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

void SqliteTestDB1Generator::BindBlobToInsertStatement(std::vector<char> b) {
	_rc = sqlite3_bind_blob(
		_preparedInsert, 
		2, 
		b.data(), 
		b.size(), 
		SQLITE_STATIC
		);
	if(_rc != SQLITE_OK) {
		throw "Can't bind blob to insert statement";
	}
}

void SqliteTestDB1Generator::ExecuteInesrtStatement() {
	_rc = sqlite3_step(_preparedInsert);
	if(_rc != SQLITE_DONE) {
		throw "Can't execute prepared insert statement";
	}
	sqlite3_reset(_preparedInsert);
}

void SqliteTestDB1Generator::FinalizeWorkWithSqlite3() {
	sqlite3_finalize(_preparedInsert);
	sqlite3_close(_db);
}

void SqliteTestDB1Generator::GenerateDataToInsert() {
	std::vector<char> blob1(3);
	std::fill(blob1.begin(), blob1.end(), '1');
	std::vector<char> blob2(6);
	std::fill(blob1.begin(), blob1.end(), '2');
	std::vector<char> blob3(9);
	std::fill(blob1.begin(), blob1.end(), '3');
	_dataToInsert["file1"] = blob1;
	_dataToInsert["file2"] = blob2;
	_dataToInsert["file3"] = blob3;
}