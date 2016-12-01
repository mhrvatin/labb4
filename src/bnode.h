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
	std::string name;
  Bnode* dotdot;

public:
	Bnode();
	Bnode(std::string path, std::string name, Bnode* dotdot);

	virtual ~Bnode() = 0;
	std::string getName() const;
	void setPath(std::string path);	
	std::string getPath() const;
	Bnode* getDotDot();
};
#endif
