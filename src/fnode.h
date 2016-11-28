#ifndef FNODE_H
#define FNODE_H

#include "bnode.h"

class Fnode: public Bnode
{

private:
	std::string fdata;

public:
	Fnode();
	Fnode(std::string fdata, std::string path, int size, std::string name, Bnode* dotdot);
	Fnode(std::string fdata);
	~Fnode();

	void setData(std::string fdata);
	std::string getData();

};
#endif
