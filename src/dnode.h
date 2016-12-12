#ifndef DNODE_H
#define DNODE_H

#include <vector>
#include "bnode.h"
#include "fnode.h"

#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

BOOST_CLASS_EXPORT_KEY(Dnode);
#endif
