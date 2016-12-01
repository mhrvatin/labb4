#include "filesystem.h"

FileSystem::FileSystem() {
  this->mRoot = new Dnode();
	  this->mWalker = Walker(this->mRoot, nullptr);
  this->mRoot->setPath("/");
  
  for (int i = 0; i < this->BLOCK_ARRAY_SIZE; i++) {
    this->blockNrs[i] = false;
  }
}

FileSystem::~FileSystem() {
			delete this->mRoot;
}

int FileSystem::createFolder(std::string folderName) {
  dynamic_cast<Dnode*>(mWalker.getLookingAt())->addNode(new Dnode(mWalker.getLookingAt()->getPath() + 
			folderName + "/", folderName, mWalker.getLookingAt()));

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
  std::cout << mWalker.getLookingAt()->getPath() << std::endl;

  return 1; // implement proper return value
}

int FileSystem::removeFile(std::string fileName) {
  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size(); i++) {
    if (files.at(i)->getName() == fileName) {
			if(dynamic_cast<Fnode*>(files.at(i)))
			{			
				hit = true;
				dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->removeNode(i);
			}
		}
	}

  if (!hit) {
    std::cout << "No such file." << std::endl;
  }
  

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
	// Fnode(std::string fdata, std::string path, int size, std::string name, Bnode* dotdot, int blockNr);
  std::string tmp;
  tmp.reserve(512);
  tmp = "test test";
  
  int blockNr = this->getFirstEmptyBlockNr();
    
  if (blockNr != -1) { // no empty blocks left
    Fnode* file = new Fnode(tmp, mWalker.getLookingAt()->getPath(), fileName, mWalker.getLookingAt(), blockNr);	

    this->setBlockNrPos(blockNr);
    dynamic_cast<Dnode*>(mWalker.getLookingAt())->addNode(file);
  } else {
    std::cout << "No empty blocks left" << std::endl; // for debug
  }
	
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

int FileSystem::goToFolder(std::string dir)
{
	
	Bnode* cdNode = findDir(dir);

	if (cdNode == nullptr)
	{
		std::cout <<"cd: " + dir + ": Not a directory" + '\n';
	}
	else
	{
		mWalker.setLookingAt(cdNode);
		mWalker.setPrev(cdNode->getDotDot());
	}
	return 1; // Fix proper return-value
}

Bnode* FileSystem::findDir(std::string dir)
{
	std::string theDir = "";
	std::vector<std::string> dirs = std::vector<std::string>();

	for(unsigned int i = 0; i < dir.size(); i++)
	{
		
		if (dir[i] == '/' || i == dir.size()-1) 
		{
			if(i == dir.size()-1)
			{
				theDir += dir[i];
			}
			dirs.push_back(theDir);
			theDir = "";
		}
		else
			theDir += dir[i];
	}
	/*
	for(unsigned int i = 0; i < dirs.size(); i++)	
	{
		std::string yolo = dirs[i];	
		std::cout << yolo + '\n'; 
	}  //FOR DEBUGGING ONLY
	*/

	return traverseTree(dirs, 0, mWalker.getLookingAt());	
}


Bnode* FileSystem::traverseTree(std::vector<std::string> dir, int size, Bnode* theNode)
{
	Bnode* returnNode = theNode;
	// std::cout << "Size of dir.size(): " << dir.size() << std::endl << "Size of size: " << size << std::endl;
	
	if(size == dir.size())
	{
		// std::cout << "REACHED BASE"; // DEBUGG ONLY
		return returnNode;
	}

	else
	{
		if (dir[size] == "..")
		{
			if (theNode->getDotDot() != nullptr)
			{	
				//std::cout << "Going back one dir" + '\n'; FOR DEBUGGING ONLY	
				returnNode = theNode->getDotDot();
			}	
		}
		else 
		{
			//std::cout << dir[size] << std::endl; # FOR DEBUGGING ONLY
			std::vector<Bnode*> files = dynamic_cast<Dnode*>(returnNode)->getFiles();

			for(unsigned int i = 0; i < files.size(); i++)
			{	
			
				if (dynamic_cast<Dnode*>(files.at(i)))
				{	
					if(dir[size] == files.at(i)->getName())
					{
						//std::cout << " CHANGING DIRECTORY " + dir[size] + '\n'; //FOR DEBUGGING ONLY
						returnNode = files.at(i);
						break;
					}
					else if (i == files.size()-1)
					{	
						size = dir.size()-1;	
						returnNode = nullptr;
					}
				}
			}
			
		}
	//std::cout << "Returning: " << size+1 << std::endl << "dir.size():" << dir.size() << std::endl; // FOR DEBUGGING ONLY
	return traverseTree(dir, size+1, returnNode);	
	}
}

void FileSystem::setBlockNrPos(int idx) {
  this->blockNrs[idx] = true;
}

void FileSystem::deleteBlockNrPos(int idx) {
  this->blockNrs[idx] = false;
}

bool FileSystem::getBlockNrStatus(int idx) {
  return this->blockNrs[idx];
}

int FileSystem::getFirstEmptyBlockNr() {
  int ret = -1;

  for (int i = 0; i < this->BLOCK_ARRAY_SIZE && ret == -1; i++) {
    if (!this->getBlockNrStatus(i)) {
      ret = i;
    }
  }

  return ret;
}
