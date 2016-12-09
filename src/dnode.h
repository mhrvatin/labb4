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
	Dnode(std::string path, std::string name, Bnode* dotdot);	
	virtual ~Dnode();
	void addNode(Bnode* node);
	std::vector<Bnode*> getFiles();
	void setFiles(std::vector<Bnode*> files);
	void removeNode(int position);
  template<typename Ar>
  void serialize(Ar& ar, const int) {
    boost::serialization::base_object<Bnode>(*this);
  }
};
#endif
