#ifndef WALKER_H
#define WALKER_H

#include <string>
#include "dnode.h"

class Walker {
private:	
	Dnode* mLookingAt;
	Dnode* mPrev;
	//std::string mCwd;

public:
	Walker();
	~Walker();
	Walker(Dnode* lookingAt, Dnode* prev);
	Dnode* getLookingAt();
	void setLookingAt(Dnode* lookingAt);
	void setPrev(Dnode* prev);
	Dnode* getPrev();
};
#endif
