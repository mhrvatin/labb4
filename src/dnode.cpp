#include "dnode.h"

Dnode::Dnode() {
	this->mFiles = std::vector<Bnode*>();
}

Dnode::Dnode(std::string path, std::string name, Bnode* dotdot):Bnode(path, name, dotdot) {
	this->mFiles = std::vector<Bnode*>();
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
