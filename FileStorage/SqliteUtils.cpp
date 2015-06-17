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
bool GenerateTestDB1(std::string db_name) {
	if(std::ifstream(db_name)) {
		if(remove(db_name.c_str()) != 0) {
			return false;
		}
	}
	sqlite3* db;
	int rc;
	char *error;
	rc = sqlite3_open(db_name.c_str(), &db);
	if(rc) {
		return false;
	}
	string sqlCreateTable = 
		"CREATE TABLE FileStorage (name TEXT PRIMARY KEY, file BLOB);";
	rc = sqlite3_exec(db, sqlCreateTable.c_str(), NULL, NULL, &error);
	if(rc) {
		return false;
	}
	sqlite3_stmt *preparedInsert;
	string sqlInsert = 
		"INSERT INTO FileStorage (name, file) values (?, ?)";
	sqlite3_prepare_v2(
		db, 
		sqlInsert.c_str(), // (const char*)
		sqlInsert.length(), // length of prepared SQL in BYTES
		&preparedInsert, // OUT: (sqlite3_stmt **) prepared stmt
		NULL // OUT: (const char**) pointer to unused portion of prepared sql string
	);
	if (rc != SQLITE_OK) {
		return false;
	}
	string s1 = "File1";
	std::vector<char> blob1;
	blob1.push_back('1');
	blob1.push_back('1');
	blob1.push_back('1');
	rc = sqlite3_bind_text(
		preparedInsert, // (sqlite3_stmt*) statement to prepare
		1, // (int) number of bind parameter
		s1.c_str(), // (const char*) binded text value
		s1.length(), // (int) size in BYTES
		SQLITE_STATIC// ( void(*)(void*) ) destructor used to dispose text or blob
		// SQLITE_STATIC - doesn't need to be freed
	);
	if (rc != SQLITE_OK) {
		return false;
	}
	rc = sqlite3_bind_blob(
		preparedInsert, 
		2, 
		blob1.data(), 
		blob1.size(), 
		SQLITE_STATIC
	);
	if(rc != SQLITE_OK) {
		return false;
	}
	rc = sqlite3_step(preparedInsert);
	if(rc != SQLITE_DONE) {
		return false;
	}
	sqlite3_finalize(preparedInsert);
	sqlite3_close(db);
	return true;
}