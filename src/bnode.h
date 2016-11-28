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
	Bnode(std::string path, int size, std::string name, Bnode* dotdot);

	virtual ~Bnode() = 0;
	virtual void setPath(std::string path) = 0;
	virtual std::string getPath() const = 0; 
  std::string getName();

};
#endif
