#include "filesystem.h"

FileSystem::FileSystem() {
  this->mRoot = new Dnode();
  this->mWalker = Walker(this->mRoot, nullptr, "/");
}

FileSystem::~FileSystem() {

			delete mRoot;
}

int FileSystem::createFolder(std::string folderName) {
  Dnode* folder = new Dnode(mWalker.getCwd(), 4, folderName, mWalker.getLookingAt());
  mRoot->addNode(folder);

  return 1; // implement proper return value
}

std::string FileSystem::listDir(std::string dir) {
  // TODO: MAKE WALKER STAND ON "PARAMETER DIR" BEFORE GETTING FILE-VECTOR.
	

  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  std::string listDirs = "";

  for (unsigned int i = 0; i < files.size(); i++) {
	
		listDirs += files.at(i)->getName() + '\n';
	}

  return listDirs;
}
int FileSystem::createFile(std::string fileName)
{
	
	Fnode* file = new Fnode("TESTING TESTING", mWalker.getCwd(), 4, fileName, mWalker.getLookingAt());	
	mRoot->addNode(file);
	
	return 1; // Fix proper return-value.
}
