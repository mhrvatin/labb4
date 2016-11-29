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
	void setPath(std::string path);	
	std::string getName() const;
	std::string getPath() const;
	Bnode* getDotDot();

};
#endif
