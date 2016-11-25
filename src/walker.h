#ifndef WALKER_H
#define WALKER_H

#include <string>
#include "bnode.h"

class Walker
{

private:	
	Bnode* lookingAt;
	Bnode* prev;

	std::string pwd;

public:
	Walker();
	~Walker();
	Walker(Bnode* lookingAt, Bnode* prev, std::string setPwd);

	std::string getPwd();
	void setPwd(std::string pwd);	
	
	//TODO: FUNCTIONS FOR SETTING NODES
};



#endif
