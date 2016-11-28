#include "dnode.h"

Dnode::Dnode()
{
	this->files = new vector<Bnode*>();
}

Dnode::Dnode(std::string path, int size, std::string name):Bnode(path, size, name)
{
	this->files = new vector<Bnode*>();
}

Dnode::~Dnode()
{
	delete files;
}
