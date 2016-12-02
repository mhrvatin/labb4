#include "bnode.h"

Bnode::Bnode()
{
	this->path = "";
	this->name = "";
	this->dotdot = nullptr;
}

Bnode::Bnode(std::string path, std::string name, Bnode* dotdot)
{
	this->path = path;
	this->name = name;
	this->dotdot = dotdot;
}

Bnode::Bnode(Bnode const& other)
{
	this->path = other.path;
	this->name = other.name;
	this->dotdot = other.dotdot;
}

Bnode::~Bnode() {
}

std::string Bnode::getName() const {
  return this->name;
}

void Bnode::setPath(std::string path)
{
	this->path = path;
}

Bnode* Bnode::getDotDot()
{
	return this->dotdot;
}

std::string Bnode::getPath() const {
	return this->path;
}

