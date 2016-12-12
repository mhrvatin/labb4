#include "bnode.h"

Bnode::Bnode() {
	this->mPath = "";
	this->mName = "";
	this->mDotdot = nullptr;
}

Bnode::Bnode(std::string path, std::string name, Bnode* dotdot) {
	this->mPath = path;
	this->mName = name;
	this->mDotdot = dotdot;
}

Bnode::Bnode(Bnode const& other) {
	this->mPath = other.mPath;
	this->mName = other.mName;
	this->mDotdot = other.mDotdot;
}

Bnode::~Bnode() { }

std::string Bnode::getName() const {
  return this->mName;
}

void Bnode::setPath(std::string path) {
	this->mPath = path;
}

Bnode* Bnode::getDotDot() {
	return this->mDotdot;
}

std::string Bnode::getPath() const {
	return this->mPath;
}
