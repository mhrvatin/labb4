#include "fnode.h"
BOOST_CLASS_EXPORT_IMPLEMENT(Fnode);

Fnode::Fnode() {
	this->mFdata = "";
  //this->blockNr = 0; // really needed? will try to save itself to on block index 0
  // implement memblockdevice, to actually write an empty file to disk
}

Fnode::Fnode(Fnode const& other) {
		//TODO: Implement mblockdevices.
		this->mFdata = other.mFdata;
}


Fnode::Fnode(std::string fdata, std::string path, std::string name, int blockNr):Bnode(path, name) {
	this->mFdata = fdata;
  this->mBlockNr = blockNr;
}

Fnode::~Fnode() {}

Fnode::Fnode(std::string fdata) {
	this->mFdata = fdata;
}

void Fnode::setData(std::string fdata) {
	this->mFdata = fdata;
}

std::string Fnode::getData() {
	return this->mFdata;
}

void Fnode::setBlockNr(int blockNr) {
  this->mBlockNr = blockNr;
}

int Fnode::getBlockNr() {
  return this->mBlockNr;
}
