#ifndef BNODE_H
#define BNODE_H

#include <string>
/*
 * PURE VIRTUAL
 */

class Bnode
{
private:
	std::string path;
	int size;
	std::string name;
  Bnode* dotdot;

public:
	
	Bnode();
	Bnode(std::string path, int size, std::string name);

	virtual ~Bnode() {};
	virtual void setPath() const = 0;
	virtual std::string getPath() = 0; 

};
#endif
