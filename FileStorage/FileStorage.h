#pragma once

#include <string>
#include <vector>

using std::string;

// Sample Interface from gMock docs to test gMock work
class Turtle {
public:
	virtual ~Turtle() {}
	virtual void PenUp() = 0;
	virtual void PenDown() = 0;
	virtual void Forward(int distance) = 0;
	virtual void Turn(int degrees) = 0;
	virtual void GoTo(int x, int y) = 0;
	virtual int GetX() const = 0;
	virtual	int GetY() const = 0;
};

class Trivial {
public:
	int ReturnOne();
};

class FileStorage {
public:
	virtual ~FileStorage() {}
	virtual void StoreFile(string name, string read_from) = 0;
	virtual void RetreiveFile(string name, string store_to) = 0;
	virtual void RemoveFile(string name) = 0;
	virtual bool HasFile(string name) = 0;
	virtual std::vector<string> GetFileNamesList() = 0;
};
