#ifndef FNODE_H
#define FNODE_H

#include "bnode.h"
#include "memblockdevice.h"

class Fnode: public Bnode {
private:
	std::string mFdata;
	int mBlockNr;
	MemBlockDevice mMemBlockDevice;

public:
	Fnode();
	Fnode(std::string fdata, std::string path, std::string name, Bnode* dotdot, int blockNr);
	Fnode(std::string fdata);
	Fnode(Fnode const& other);
	~Fnode();

	void setData(std::string fdata);
	std::string getData();
	int getBlockNr();
	void setBlockNr(int blockNr);
};
#endif
