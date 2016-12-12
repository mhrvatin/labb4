#ifndef BNODE_H
#define BNODE_H

#include <string>

/*
 * PURE VIRTUAL
 */

class Bnode {
private:
	std::string mPath;
	std::string mName;
 
public:
	Bnode();
	Bnode(std::string path, std::string name);
	Bnode(Bnode const& other);

	virtual ~Bnode() = 0;
	std::string getName() const;
	void setPath(std::string path);	
	std::string getPath() const;
};
#endif
