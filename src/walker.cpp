#include "walker.h"

Walker::Walker() {
	this->mLookingAt = nullptr;
	this->mPrev = nullptr;
}

Walker::~Walker() {}

Walker::Walker(Dnode* lookingAt, Dnode* prev) {
	this->mLookingAt = lookingAt;
	this->mPrev = prev;
}

Dnode* Walker::getLookingAt() {
  return this->mLookingAt;
}


void Walker::setLookingAt(Dnode* lookingAt) {		
	this->mLookingAt = lookingAt;
}

void Walker::setPrev(Dnode* prev) {
	this->mPrev = prev;
}

Dnode* Walker::getPrev() {
	return this->mPrev;
}
