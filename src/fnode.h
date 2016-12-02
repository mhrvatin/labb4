#ifndef FNODE_H
#define FNODE_H

#include "bnode.h"
#include "memblockdevice.h"

class Fnode: public Bnode
{

private:
	std::string mFdata;
  int mBlockNr;

public:
	Fnode();
	Fnode(std::string fdata, std::string path, std::string name, Bnode* dotdot, int blockNr);
	Fnode(std::string fdata);
	~Fnode();

	void setData(std::string fdata);
	std::string getData();
  void setBlockNr(int blockNr);
  int getBlockNr();
};
#endif
