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
	Dnode(std::string path, int size, std::string name, Bnode* dotdot);	
	virtual ~Dnode();
	int addNode(Bnode* node);
	std::vector<Bnode*> getFiles();
	void setFiles(std::vector<Bnode*> files);
	int removeNode(int position);
};
#endif
