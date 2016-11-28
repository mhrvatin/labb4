#include "filesystem.h"

FileSystem::FileSystem() {
  this->mRoot = new Dnode();
  this->mWalker = Walker(this->mRoot, nullptr, "/");
}

FileSystem::~FileSystem() {

}

int FileSystem::createFolder(std::string folderName) {
  Dnode* folder = new Dnode(mWalker.getCwd(), 4, folderName, mWalker.getLookingAt());
  mRoot->addNode(folder);

  return 1; // implement proper return value
}

std::string FileSystem::listDir(std::string dir) {
  std::vector<Bnode*> files = this->mRoot->getFiles();

  for (int i = 0; i < files.size(); i++) {
    //std::cout << i << std::endl;
    std::cout << dynamic_cast<Dnode*>(files.at(i))->getName() << std::endl;
    //std::cout << files.at(i)->getName() << std::endl;
  }

  return "";
}
