#include "dnode.h"

Dnode::Dnode() {
	this->mFiles = std::vector<Bnode*>();
	this->mDotdot = nullptr;
}

Dnode::Dnode(std::string path, std::string name, Dnode* dotdot):Bnode(path, name) {
	this->mFiles = std::vector<Bnode*>();
	this->mDotdot = dotdot;
}

Dnode::~Dnode() {
  for(unsigned int i = 0; i < this->mFiles.size(); i++) {
		delete this->mFiles[i];
	}
}

void Dnode::addNode(Bnode* node) {
  this->mFiles.push_back(node);
}

std::vector<Bnode*> Dnode::getFiles() {
  return this->mFiles;
}

void Dnode::setFiles(std::vector<Bnode*> files) {
  this->mFiles = files;
}

void Dnode::removeNode(int position) {
	Bnode* theNode = this->mFiles.at(position);
	this->mFiles.erase(this->mFiles.begin() + position);

  delete theNode;
}

Dnode* Dnode::getDotDot() {
  return this->mDotdot;
}
