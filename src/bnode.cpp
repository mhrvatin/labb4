#include "bnode.h"

Bnode::Bnode()
{
	this->path = "";
	this->size = 0;
	this->name = "";
}

Bnode::Bnode(std::string path, int size, std::string name)
{
	this->path = path;
	this->size = size;
	this->name = name;
}
