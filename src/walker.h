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
	Walker(Bnode* lookingAt, Bnode* prev, std::string cwd);

	std::string getCwd();
	Bnode* getLookingAt();
	void setCwd(std::string cwd);	
	
	//TODO: FUNCTIONS FOR SETTING NODES
	
	void setLookingAt(Bnode* lookingAt, Bnode* prev);
};



#endif
