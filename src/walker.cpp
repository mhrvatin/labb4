#include "walker.h"

Walker::Walker()
{
	
	this->lookingAt = NULL;
	this->prev = NULL;
	this->pwd = "";
}

Walker::~Walker()
{
	// NEEDS TO BE DELETED(!?)
	delete lookingAt;
	delete prev;	
}

Walker::Walker(Bnode* lookingAt, Bnode* prev, std::string pwd)
{
	this->lookingAt = lookingAt;
	this->prev = prev;
	this->pwd = pwd;
}

std::string Walker::getPwd()
{
	return this->pwd;
}

void Walker::setPwd(std::string pwd)
{
	this->pwd = pwd;
}

