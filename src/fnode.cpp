#include "fnode.h"

Fnode::Fnode()
{
	this->fdata = "";
}

Fnode::Fnode(std::string fdata, std::string path, int size, std::string name):Bnode(path, size, name)
{
	this->fdata = fdata;
}

Fnode::~Fnode()
{
	// Only for declaring, does nothing
}

Fnode::Fnode(std::string fdata)
{
	this->fdata = fdata;
}

void Fnode::setData(std::string fdata)
{
	this->fdata = fdata;
}

std::string Fnode::getData()
{
	return this->fdata;
}
