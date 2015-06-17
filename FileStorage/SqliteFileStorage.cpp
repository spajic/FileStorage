#include "SqliteFileStorage.h"

#include <fstream>
#include <vector>

#include "FileUtils.h"

#include "sqlite3.h"

SqliteFileStorage::SqliteFileStorage() {
	InitDatabase("MyDb.db");
}

void SqliteFileStorage::InitDatabase(std::string file_name) {
	db_name = file_name;
	int rc;
	char *error;
	rc = sqlite3_open(db_name.c_str(), &db);
	const char *sqlCreateTable = "CREATE TABLE MyTable (id INTEGER PRIMARY KEY, value STRING);";
	rc = sqlite3_exec(db, sqlCreateTable, NULL, NULL, &error);
	const char *sqlInsert = "INSERT INTO MyTable VALUES(NULL, 'A Value');";
	rc = sqlite3_exec(db, sqlInsert, NULL, NULL, &error);
	const char *sqlSelect = "SELECT * FROM MyTable;";
	char **results = NULL;
	int rows, columns;
	sqlite3_get_table(db, sqlSelect, &results, &rows, &columns, &error);
	
	sqlite3_free_table(results);
	//else
	//{
	//	// Display Table
	//	for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
	//	{
	//		for (int colCtr = 0; colCtr < columns; ++colCtr)
	//		{
	//			// Determine Cell Position
	//			int cellPosition = (rowCtr * columns) + colCtr;

	//			// Display Cell Value
	//			cout.width(12);
	//			cout.setf(ios::left);
	//			cout << results[cellPosition] << " ";
	//		}

	//		// End Line
	//		cout << endl;

	//		// Display Separator For Header
	//		if (0 == rowCtr)
	//		{
	//			for (int colCtr = 0; colCtr < columns; ++colCtr)
	//			{
	//				cout.width(12);
	//				cout.setf(ios::left);
	//				cout << "~~~~~~~~~~~~ ";
	//			}
	//			cout << endl;
	//		}
	//	}
	//}

}

SqliteFileStorage::~SqliteFileStorage() {
	sqlite3_close(db);
}

void SqliteFileStorage::StoreFile(string name, string read_from) {
	std::vector<char> chars;
	FileUtils::ReadFileToVectorOfChars(read_from, &chars);
}

bool SqliteFileStorage::HasFile(string name) {
	return true;
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

