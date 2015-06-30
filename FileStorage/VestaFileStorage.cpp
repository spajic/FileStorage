#include "VestaFileStorage.h"

VestaFileStorage::VestaFileStorage()
{

}

VestaFileStorage::~VestaFileStorage()
{

}

void VestaFileStorage::StoreFile(string name, string read_from)
{

}

void VestaFileStorage::RetreiveFile(string name, string store_to)
{

}

void VestaFileStorage::RemoveFile(string name)
{

}

bool VestaFileStorage::HasFile(string name)
{
	return true;
}

std::vector<string> VestaFileStorage::GetFileNamesList()
{
	std::vector<string> res;
	res.push_back("hello from Vesta");
	return res;
}
