// FileStorageTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "FileStorage\FileStorage.h"

TEST(FirstTest, Pass) {
	Trivial t;
	EXPECT_EQ(1, t.ReturnOne());
}

class MockTurtle : public Turtle {
public:
	MOCK_METHOD0(PenUp, void());
	MOCK_METHOD0(PenDown, void());
	MOCK_METHOD1(Forward, void(int distance));
	MOCK_METHOD1(Turn, void(int degrees));
	MOCK_METHOD2(GoTo, void(int x, int y));
	MOCK_CONST_METHOD0(GetX, int());
	MOCK_CONST_METHOD0(GetY, int());
};

TEST(PainterTest, CanDrawSomething) {
	MockTurtle Turtle;	
	EXPECT_CALL(Turtle, PenDown())
		.Times(::testing::AtLeast(1));
	Turtle.PenDown();
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

