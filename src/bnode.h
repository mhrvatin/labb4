#ifndef BNODE_H
#define BNODE_H

#include <string>
#include <boost/serialization/export.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

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
	Bnode(Bnode const& other);

	virtual ~Bnode() = 0;
	std::string getName() const;
	void setPath(std::string path);	
	std::string getPath() const;
	Bnode* getDotDot();
 
  template <typename Ar>
    void serialize(Ar& ar, const int) {
  }
};

BOOST_CLASS_EXPORT_KEY(Bnode);
#endif
