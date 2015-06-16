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
	const string generated_file_path = "FileUtilsTest.bin";
	std::ofstream generated_file(generated_file_path, std::ios::binary);
	for (char b : generated_chars) {
		generated_file << b;
	}
	generated_file.close();

	vector<char> retreived_chars;
	FileUtils::ReadFileToVectorOfChars(generated_file_path, &retreived_chars);
	ASSERT_EQ(generated_chars.size(), retreived_chars.size());
	EXPECT_EQ(true,
		std::equal(
		generated_chars.begin(), generated_chars.end(), retreived_chars.begin()
		)
	);
}

TEST(FileUtilsTest, CanWriteVectorOfCharsToFile) {
	vector<char> generated_chars{ 't', 'e', 's', 't', ' ', 'u', 't', 'i', 'l', 's' };
	string written_file_name = "FileUtilsWriteVectorOfCharsTest.bin";
	FileUtils::WriteVectorOfCharsToFile(written_file_name, &generated_chars);
	vector<char> read_chars;
	FileUtils::ReadFileToVectorOfChars(written_file_name, &read_chars);
	ASSERT_EQ(generated_chars.size(), read_chars.size());
	EXPECT_EQ(true,
		std::equal(
		generated_chars.begin(), generated_chars.end(), read_chars.begin()
		)
	);
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
	EXPECT_EQ(names_to_store.size(), result_names_list.size());
	EXPECT_EQ(
		true, std::equal(
			names_to_store.begin(), names_to_store.end(), 
			result_names_list.begin()
		)
	);
}

TEST(RamFileStorageRetreiveTest, NoThrowForAbsentFile) {
	RamFileStorage fs;
	EXPECT_NO_THROW({
		fs.RetreiveFile("absent file name", "fake_path");
	});
}

TEST(RamFileStorageRetreiveTest, RetreivesFileExectlyAsItWasStored) {
	RamFileStorage fs;
	vector<char> generated_bytes{ 'H', 'e', 'l', 'l', 'o' };
	const string generated_file_path = "generated.bin";
	const string generated_file_name = "generated";
	std::ofstream generated_file(generated_file_path, std::ios::binary);
	for (char b : generated_bytes) {
		generated_file << b;
	}
	const string retreived_file_path = "retreived.bin";
	fs.RetreiveFile(generated_file_name, retreived_file_path);
	vector<char> retreived_bytes;
	FileUtils::ReadFileToVectorOfChars(retreived_file_path, &retreived_bytes);
		
	ASSERT_EQ(generated_bytes.size(), retreived_bytes.size());
	EXPECT_EQ(true,
		std::equal(
			generated_bytes.begin(), generated_bytes.end(), retreived_bytes.begin()
		)
	);
}

//TEST(RamFileStorageTest, MakesSomeWork) {
//	RamFileStorage fs;
//}


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

