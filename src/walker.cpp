#include "walker.h"

Walker::Walker()
{
	this->lookingAt = nullptr;
	this->prev = nullptr;

}

Walker::~Walker()
{

}

Walker::Walker(Bnode* lookingAt, Bnode* prev)
{
	this->lookingAt = lookingAt;
	this->prev = prev;
	
}

Bnode* Walker::getLookingAt() {
  return this->lookingAt;
}


void Walker::setLookingAt(Bnode* lookingAt)
{		
	this->lookingAt = lookingAt;
}

void Walker::setPrev(Bnode* prev)
{
	this->prev = prev;
}

Bnode* Walker::getPrev()
{
	return this->prev;
}
