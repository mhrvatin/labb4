#ifndef DNODE_H
#define DNODE_H

#include <vector>
#include "bnode.h"

class Dnode: public Bnode
{
private:
	std::vector<Bnode*> files;

public:
	Dnode();
	Dnode(std::string path, int size, std::string name);	
	~Dnode();

	

};
#endif
