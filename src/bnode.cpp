#include "bnode.h"

Bnode::Bnode()
{
	this->path = "";
	this->size = 0;
	this->name = "";
  this->dotdot = nullptr;
}

Bnode::Bnode(std::string path, int size, std::string name, Bnode* dotdot)
{
	this->path = path;
	this->size = size;
	this->name = name;
	this->dotdot = dotdot;
}

Bnode::~Bnode() {
}

std::string Bnode::getName() const {
  return this->name;
}

std::string Bnode::getPath() const {
	return this->path;
}

void Bnode::setPath(std::string path)
{
	this->path = path;
}

