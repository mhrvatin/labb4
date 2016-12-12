#ifndef DNODE_H
#define DNODE_H

#include <vector>
#include "bnode.h"
#include "fnode.h"

BOOST_CLASS_EXPORT_KEY(Fnode);

class Dnode: public Bnode {
private:
	std::vector<Bnode*> mFiles;
	Dnode* mDotdot;

public:
	Dnode();
	Dnode(std::string path, std::string name, Dnode* dotdot);	
	virtual ~Dnode();
	void addNode(Bnode* node);
	std::vector<Bnode*> getFiles();
	void setFiles(std::vector<Bnode*> files);
	void removeNode(int position);
	Dnode* getDotDot();

  friend class boost::serialization::access;

  template<typename Ar>
  void serialize(Ar& ar, const int version) {
    ar & boost::serialization::base_object<Bnode>(*this);
    ar & this->mFiles;
    ar & this->mDotdot;
  }
};

#endif
