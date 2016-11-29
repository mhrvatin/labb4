#include "walker.h"

Walker::Walker()
{
	this->lookingAt = nullptr;
	this->prev = nullptr;
	this->cwd = "";
}

Walker::~Walker()
{

}

Walker::Walker(Bnode* lookingAt, Bnode* prev, std::string cwd)
{
	this->lookingAt = lookingAt;
	this->prev = prev;
	this->cwd = cwd;
}

std::string Walker::getCwd()
{
	return this->cwd;
}

Bnode* Walker::getLookingAt() {
  return this->lookingAt;
}

void Walker::setCwd(std::string cwd)
{
	this->cwd = cwd;
}

void Walker::setLookingAt(Bnode* lookingAt, Bnode* prev)
{	
	this->prev = prev;	
	this->lookingAt = lookingAt;
}
