#include "bnode.h"
BOOST_CLASS_EXPORT_IMPLEMENT(Bnode);
Bnode::Bnode() {
	this->mPath = "";
	this->mName = "";
}

Bnode::Bnode(std::string path, std::string name) {
	this->mPath = path;
	this->mName = name;
}

Bnode::Bnode(Bnode const& other) {
	this->mPath = other.mPath;
	this->mName = other.mName;
}

Bnode::~Bnode() { }

std::string Bnode::getName() const {
  return this->mName;
}

void Bnode::setPath(std::string path) {
	this->mPath = path;
}

std::string Bnode::getPath() const {
	return this->mPath;
}
