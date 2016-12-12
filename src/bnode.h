#ifndef BNODE_H
#define BNODE_H

#include <string>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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

  friend class boost::serialization::access;

  template <typename Ar>
  void serialize(Ar& ar, const int version) {
    ar & this->mPath;
    ar & this->mName;
  }
};

BOOST_CLASS_EXPORT_KEY(Bnode);
#endif
