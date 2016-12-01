#include "dnode.h"

Dnode::Dnode()
{
	this->files = std::vector<Bnode*>();
}

Dnode::Dnode(std::string path, std::string name, Bnode* dotdot):Bnode(path, name, dotdot)
{
	this->files = std::vector<Bnode*>();
}

Dnode::~Dnode()
{
	//delete files; // implement proper delete to avoid memory leaks
		for(unsigned int i = 0; i < this->files.size(); i++)
	{
		delete this->files[i];
	}
}

int Dnode::addNode(Bnode* node) {
  this->files.push_back(node);

  return 1; // implement proper return value
}

std::vector<Bnode*> Dnode::getFiles() {
  return this->files;
}

void Dnode::setFiles(std::vector<Bnode*> files) {
  this->files = files;
}
