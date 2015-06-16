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

#include "FileStorage\FileStorage.h"
#include "FileStorage\RamFileStorage.h"
#include "FileStorage\FileUtils.h"

using std::string;
using std::vector;

const string kTempPath = "tests_temp\\";

//class MockTurtle : public Turtle {
//public:
//	MOCK_METHOD0(PenUp, void());
//	MOCK_METHOD0(PenDown, void());
//	MOCK_METHOD1(Forward, void(int distance));
//	MOCK_METHOD1(Turn, void(int degrees));
//	MOCK_METHOD2(GoTo, void(int x, int y));
//	MOCK_CONST_METHOD0(GetX, int());
//	MOCK_CONST_METHOD0(GetY, int());
//};
//
//TEST(PainterTest, CanDrawSomething) {
//	MockTurtle Turtle;
//	EXPECT_CALL(Turtle, PenDown())
//		.Times(::testing::AtLeast(1));
//	Turtle.PenDown();
//}

TEST(FileUtilsTest, CanReadFileToVectorOfChars) {
	vector<char> generated_chars{'t', 'e', 's', 't', ' ', 'u', 't', 'i', 'l', 's' };
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
	vector<char> generated_chars{ 't', 'e', 's', 't', ' ', 'u', 't', 'i', 'l', 's' };
	string written_file_name = kTempPath + "FileUtilsWriteVectorOfCharsTest.bin";
	FileUtils::WriteVectorOfCharsToFile(written_file_name, generated_chars);
	vector<char> read_chars;
	FileUtils::ReadFileToVectorOfChars(written_file_name, &read_chars);
	ASSERT_EQ(true, generated_chars == read_chars);
}

TEST(RamFileStorageTest, CanCreateClass) {
	RamFileStorage fs;
}

TEST(RamFileStorageHasFileTest, ReturnsFalseForAbsentFile) {
	RamFileStorage fs;
	EXPECT_EQ(false, fs.HasFile("any name"));
}

TEST(RamFileStorageHasFileTest, ReturnsTrueForStoredFile) {
	 RamFileStorage fs;
	 string read_from = "fake path";
	 string stored_file_name = "first stored file";
	 EXPECT_EQ(false, fs.HasFile(stored_file_name));
	 fs.StoreFile(stored_file_name, read_from);
	 EXPECT_EQ(true, fs.HasFile(stored_file_name));
}

TEST(RamFileStorageRemoveTest, DoNotThrowOnAttemptToRemoveAbsentFile) {
	RamFileStorage fs;
	EXPECT_NO_THROW({
		fs.RemoveFile("absent file name");
	});
}

TEST(RamFileStorageRemoveTest, RemovedFileNotDetectedByHasFile) {
	RamFileStorage fs;
	string read_from = "fake path";
	string really_stored_file_name = "file1";
	fs.StoreFile(really_stored_file_name, read_from);
	EXPECT_EQ(true, fs.HasFile(really_stored_file_name));
	fs.RemoveFile(really_stored_file_name);
	EXPECT_EQ(false, fs.HasFile(really_stored_file_name));
}

TEST(RamFileStorageGetFileNamesLitsTest, ReturnsEmptyListWhenNothingStored) {
	RamFileStorage fs;
	vector<string> results;
	results = fs.GetFileNamesList();
	EXPECT_EQ(0, results.size());
}

TEST(RamFileStorageGetFileNamesLitsTest, ReturnsCorrectListForSomeStoredFiles) {
	RamFileStorage fs;
	string fake_path = "fake path";
	vector<string> names_to_store{"file1", "file2", "file3"};
	for (auto name : names_to_store)	{
		fs.StoreFile(name, fake_path);
	}
	vector<string> result_names_list = fs.GetFileNamesList();
	ASSERT_EQ(true, names_to_store == result_names_list);
}

TEST(RamFileStorageRetreiveTest, NoThrowForAbsentFile) {
	RamFileStorage fs;
	EXPECT_NO_THROW({
		fs.RetreiveFile("absent file name", kTempPath + "fake_path.bin");
	});
}

TEST(RamFileStorageRetreiveTest, RetreivesFileExectlyAsItWasStored) {
	RamFileStorage fs;
	vector<char> generated_bytes{ 'H', 'e', 'l', 'l', 'o', 'F', 'S'};
	const string generated_file_path = kTempPath + "generated.bin";
	const string generated_file_name = "generated";
	FileUtils::WriteVectorOfCharsToFile(generated_file_path, generated_bytes);
	const string retreived_file_path = kTempPath + "retreived.bin";
	vector<char> retreived_bytes;

	fs.StoreFile(generated_file_name, generated_file_path);
	fs.RetreiveFile(generated_file_name, retreived_file_path);
	
	FileUtils::ReadFileToVectorOfChars(retreived_file_path, &retreived_bytes);
	ASSERT_EQ(true, generated_bytes == retreived_bytes);
}

TEST(RamFileStorageTest, StoresAndRetreivesRealFile) {
	RamFileStorage fs;
	string real_file_path = kTempPath + "pic.jpg";
	string retreive_path = kTempPath + "retreived_pic.jpg";
	string real_file_name = "pic";
	fs.StoreFile(real_file_name, real_file_path);
	fs.RetreiveFile(real_file_name, retreive_path);
	
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

