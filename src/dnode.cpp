#include "dnode.h"

Dnode::Dnode()
{
	this->files = std::vector<Bnode*>();
}

Dnode::Dnode(std::string path, int size, std::string name, Bnode* dotdot):Bnode(path, size, name, dotdot)
{
	this->files = std::vector<Bnode*>();
}

Dnode::~Dnode()
{
	//delete files; // implement proper delete to avoid memory leaks
}

void Dnode::setPath(std::string path) {
  
}

std::string Dnode::getPath() const {
  return "tempPath";
}

int Dnode::addNode(Bnode* node) {
  this->files.push_back(node);

  return 1; // implement proper return value
}

std::vector<Bnode*> Dnode::getFiles() {
  return this->files;
}
