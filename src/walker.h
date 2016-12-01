#ifndef WALKER_H
#define WALKER_H

#include <string>
#include "bnode.h"

class Walker
{

private:	
	Bnode* lookingAt;
	Bnode* prev;
	std::string cwd;

public:
	Walker();
	~Walker();
	Walker(Bnode* lookingAt, Bnode* prev);


	Bnode* getLookingAt();
	Bnode* getPrev();
	
	void setLookingAt(Bnode* lookingAt);
	void setPrev(Bnode* prev);
};



#endif
