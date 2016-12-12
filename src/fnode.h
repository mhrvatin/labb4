#ifndef FNODE_H
#define FNODE_H

#include "bnode.h"
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Fnode: public Bnode {
private:
	std::string mFdata;
	int mBlockNr;

public:
	Fnode();
	Fnode(std::string fdata, std::string path, std::string name, int blockNr);
	Fnode(std::string fdata);
	Fnode(Fnode const& other);
	~Fnode();

	void setData(std::string fdata);
	std::string getData();
	int getBlockNr();
	void setBlockNr(int blockNr);

  friend class boost::serialization::access;
  template<typename Ar>
  void serialize(Ar& ar, const int version) {
    ar & boost::serialization::base_object<Bnode>(*this);
    ar & this->mFdata;
    ar & this->mBlockNr;
  }
};

BOOST_CLASS_EXPORT_KEY(Fnode);
#endif
