#ifndef DNODE_H
#define DNODE_H

#include <vector>
#include "bnode.h"

class Dnode: public Bnode
{
private:
	std::vector<Bnode*> files;
	Dnode* parent;

public:
	Dnode(Dnode* parent); 
	// TODO: IMPLEMENT CONSTRUCTOR FOR INHERITENCE.
	
	~Dnode();

	//TODO: IMPLEMENT NECCESSARY THINGS, like GET SET

};
#endif
