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

int FileSystem::printContents(std::string fileName) {
  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size() && !hit; i++) {
    if (dynamic_cast<Fnode*>(files.at(i)) && files.at(i)->getName() == fileName) {
      hit = true;
      std::cout << dynamic_cast<Fnode*>(files.at(i))->getData() << std::endl;
    }
	}

  if (!hit) {
    std::cout << "No such file" << std::endl;
  }

  return 1; // implement proper return value
}

int FileSystem::printCurrentWorkingDirectory() {
  std::cout << mWalker.getCwd() << std::endl;

  return 1; // implement proper return value
}

int FileSystem::removeFile(std::string fileName) {
  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size(); i++) {
    if (files.at(i)->getName() == fileName) {
      hit = true;
      
      files.erase(files.begin() + i);
    }
	}

  if (!hit) {
    std::cout << "No such file or directory" << std::endl;
  }

  dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->setFiles(files);

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

int FileSystem::createImage() {
  /*std::string loggedInUser = getlogin();
  std::string path = "/home/" + loggedInUser + "/labb4_filesystem_image";
  std::cout << loggedInUser << std::endl; // print logged in user

  //std::ofstream fsImage(path, std::ios::out | std::ofstream::binary);
  //std::copy(mRoot->getFiles().begin(), mRoot->getFiles().end(), std::ostreambuf_iterator<char>(fsImage));
  std::ofstream fsImage(path);
  std::ostream_iterator<std::string> output_iterator(fsImage, "\n");
  std::copy(mRoot->getFiles().begin, mRoot->getFiles().end(), output_iterator);*/

  return 1; // fix proper return value
}
