// FileStorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <fstream>
#include <iterator>
#include <vector>
#include <string>
#include <memory>

#include "FileStorage\FileStorage.h"
#include "FileStorage\RamFileStorage.h"
#include "FileStorage\SqliteFileStorage.h"
#include "FileStorage\FileUtils.h"
#include "FileStorage\SqliteUtils.h"

using std::string;
using std::vector;

const string kTempPath = "tests_temp\\";

//----------------------- Test File Utils -------------------------------
TEST(FileUtilsTest, CanReadFileToVectorOfChars) {
	static const char arr[] = {'t', 'e', 's', 't', ' ', 'u', 't', 'i', 'l', 's' };
	vector<char> generated_chars(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	const string generated_file_path = kTempPath + "FileUtilsTest.bin";
	std::ofstream generated_file(generated_file_path, std::ios::binary);
	for (char b : generated_chars) {
		generated_file << b;
	}
	generated_file.close();

	vector<char> retreived_chars;
	FileUtils::ReadFileToVectorOfChars(generated_file_path, &retreived_chars);
	ASSERT_EQ(true, generated_chars == retreived_chars);
}

TEST(FileUtilsTest, CanWriteVectorOfCharsToFile) {
	static const char arr[] = {'t', 'e', 's', 't', ' ', 'u', 't', 'i', 'l', 's' };
	vector<char> generated_chars(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	string written_file_name = kTempPath + "FileUtilsWriteVectorOfCharsTest.bin";
	FileUtils::WriteVectorOfCharsToFile(written_file_name, generated_chars);
	vector<char> read_chars;
	FileUtils::ReadFileToVectorOfChars(written_file_name, &read_chars);
	ASSERT_EQ(true, generated_chars == read_chars);
}

//----------------------- Test File Utils -------------------------------
TEST(SqliteUtils, CanCreateTestDB1) {
	ASSERT_EQ(true, GenerateTestDB1(kTempPath + "testDB1.db"));
}

//-------------------- Test instantiation of FileStorage implementations ------
TEST(RamFileStorageTest, CanCreateClass) {
	RamFileStorage fs;
}

//------------------- Setup Value-parametrized tests for FileStorage ----------
class FileStorageTest : public ::testing::TestWithParam<string> {
protected:
	std::unique_ptr<FileStorage> fs;

	virtual void SetUp() {
		string fs_impl = GetParam();
		if(fs_impl == "Ram") {
			fs = std::unique_ptr<FileStorage>(new RamFileStorage);
		}
		else if(fs_impl == "Sqlite") {
			fs = std::unique_ptr<FileStorage>(new SqliteFileStorage);
		}
	}
};

const string fs_implementations[] = {"Ram", "Sqlite"};
INSTANTIATE_TEST_CASE_P(TestFileStorageImpls,
												FileStorageTest,
												::testing::ValuesIn(fs_implementations)
);


//--------------------- FileStorage Tests ------------------------------
TEST_P(FileStorageTest, HasFileReturnsFalseForAbsentFile) {
	EXPECT_EQ(false, fs->HasFile("any name"));
}

TEST_P(FileStorageTest, HasFileReturnsTrueForStoredFile) {
	string read_from = "fake path";
	string stored_file_name = "first stored file";

	EXPECT_EQ(false, fs->HasFile(stored_file_name));
	fs->StoreFile(stored_file_name, read_from);
	EXPECT_EQ(true, fs->HasFile(stored_file_name));
}

TEST_P(FileStorageTest, RemoveFileDoNotThrowOnAttemptToRemoveAbsentFile) {
	EXPECT_NO_THROW({
		fs->RemoveFile("absent file name");
	});
}

TEST_P(FileStorageTest, RemovedFileNotDetectedByHasFile) {
	string read_from = "fake path";
	string really_stored_file_name = "file1";
	fs->StoreFile(really_stored_file_name, read_from);
	EXPECT_EQ(true, fs->HasFile(really_stored_file_name));
	fs->RemoveFile(really_stored_file_name);
	EXPECT_EQ(false, fs->HasFile(really_stored_file_name));
}

TEST_P(FileStorageTest, GetFileNamesLitsReturnsEmptyListWhenNothingStored) {
	vector<string> results;
	results = fs->GetFileNamesList();
	EXPECT_EQ(0, results.size());
}

TEST_P(FileStorageTest, GetFileNamesLitsReturnsCorrectListForSomeStoredFiles) {
	string fake_path = "fake path";
	static const string arr[] = {"file1", "file2", "file3"};
	vector<string> names_to_store(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	for (auto name : names_to_store)	{
		fs->StoreFile(name, fake_path);
	}
	vector<string> result_names_list = fs->GetFileNamesList();
	ASSERT_EQ(true, names_to_store == result_names_list);
}

TEST_P(FileStorageTest, RetreiveNoThrowForAbsentFile) {
	EXPECT_NO_THROW({
		fs->RetreiveFile("absent file name", kTempPath + "fake_path.bin");
	});
}

TEST_P(FileStorageTest, RetreivesFileExectlyAsItWasStored) {
	static const char arr[] = { 'H', 'e', 'l', 'l', 'o', 'F', 'S'};
	vector<char> generated_bytes(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	const string generated_file_path = kTempPath + "generated.bin";
	const string generated_file_name = "generated";
	FileUtils::WriteVectorOfCharsToFile(generated_file_path, generated_bytes);
	const string retreived_file_path = kTempPath + "retreived.bin";
	vector<char> retreived_bytes;

	fs->StoreFile(generated_file_name, generated_file_path);
	fs->RetreiveFile(generated_file_name, retreived_file_path);

	FileUtils::ReadFileToVectorOfChars(retreived_file_path, &retreived_bytes);
	ASSERT_EQ(true, generated_bytes == retreived_bytes);
}

TEST_P(FileStorageTest, StoresAndRetreivesRealFile) {
	string real_file_path = kTempPath + "pic.jpg";
	string retreive_path = kTempPath + "retreived_pic.jpg";
	string real_file_name = "pic";
	fs->StoreFile(real_file_name, real_file_path);
	fs->RetreiveFile(real_file_name, retreive_path);

	vector<char> stored_chars;
	FileUtils::ReadFileToVectorOfChars(real_file_path, &stored_chars);

	vector<char> retreived_chars;
	FileUtils::ReadFileToVectorOfChars(retreive_path, &retreived_chars);

	ASSERT_EQ(stored_chars, retreived_chars);
}


int runAllTests(int argc, char* argv[]) {
	std::cout << "\nRunning tests...\n\n";
	return RUN_ALL_TESTS();
}

int _tmain(int argc, char* argv[])
{
	std::cout << "Hello, FileStorageTest!\n";
	
	::testing::InitGoogleTest(&argc, argv);
	::testing::InitGoogleMock(&argc, argv);
	::runAllTests(argc, argv);

	std::cout << "\nPress enter to exit.";
	std::cin.get();
	return 0;
}

