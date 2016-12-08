#include "filesystem.h"


FileSystem::FileSystem() {
  this->mMemBlockDevice = MemBlockDevice(this->BLOCK_ARRAY_SIZE);
  this->format();
}

FileSystem::~FileSystem() {
			delete this->mRoot;
}
int FileSystem::createFolder(std::string folderName) {
  int ret = -1;
  std::vector<std::string> destFile = seperateDir(folderName); 
  Bnode* destination;
  
  if (destFile[0] != "")
  {
	destination = findDir(destFile[0]);
	if(destination == nullptr)
	{
		return ret;
	}
  }
  else
  {
	destination = mWalker.getLookingAt();
  }


  dynamic_cast<Dnode*>(destination)->addNode(new Dnode(destination->getPath() + 
			destFile[1] + "/", destFile[1], destination));

  return 1; // implement proper return value
}

std::string FileSystem::printContents(std::string fileName) {
  std::string contents = "No such file or directory";

  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size() && !hit; i++) {
    if (dynamic_cast<Fnode*>(files.at(i)) && files.at(i)->getName() == fileName) {
      hit = true;
      Fnode* foundFile = dynamic_cast<Fnode*>(files.at(i));

      Block block = this->mMemBlockDevice.readBlock(foundFile->getBlockNr());
      contents = block.toString();
		}
	}

  return contents; 
}

std::string FileSystem::printCurrentWorkingDirectory() {
  return mWalker.getLookingAt()->getPath();
}

int FileSystem::removeFile(std::string fileName) {
  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size() && !hit; i++) {
    if (files.at(i)->getName() == fileName) {
			if(dynamic_cast<Fnode*>(files.at(i)))
			{			
				hit = true;
        Fnode* fileToDelete = dynamic_cast<Fnode*>(files.at(i));

				dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->removeNode(i);
        this->deleteBlockNrPos(fileToDelete->getBlockNr()); // set file's block position as empty
			}
		}
	}

  if (!hit) {
    std::cout << "No such file." << std::endl;
  }

  return 1; // implement proper return value
}

std::string FileSystem::listDir(std::string dir) { 
	Bnode* cdDir;

	if(dir == "") 
	{
		cdDir = mWalker.getLookingAt();	
	}
	else
	{
		cdDir = findDir(dir);
	}
	
	std::string listDirs = "";

	if (cdDir != nullptr)
	{
		std::vector<Bnode*> files = dynamic_cast<Dnode*>(cdDir)->getFiles(); 
		for (unsigned int i = 0; i < files.size(); i++) 
		{
			listDirs += files.at(i)->getName() + '\n';
		}
	}
	else
	{
		listDirs = "Couldn't find folder " + dir + '\n';
	}	


		return listDirs;
}

int FileSystem::createFile(std::string fileName) {
  int ret = -1;	
  std::vector<std::string> destFile = seperateDir(fileName);
  Bnode* destination;
  
  if (destFile[0] != "")
  {
	destination = findDir(destFile[0]);
	if(destination == nullptr)
	{
		return ret;
	}
  }
  else
  {
	destination = mWalker.getLookingAt();
  }

 if (fileName.length() > 0) {
    ret = 1;
    std::string tmp;
    int blockNr = this->getFirstEmptyBlockNr();

    tmp = "test test"; // TODO: user should be able to input text in file by themself 
    tmp.resize(512);

    if (blockNr != -1) { // empty blocks are still available
      Fnode* file = new Fnode(tmp, destination->getPath(), destFile[1], destination, blockNr);	
      std::string tmp = file->getData();
      
      if (mMemBlockDevice.writeBlock(blockNr, file->getData()) != 1) {
        ret = -1; // generic error
      }

      this->setBlockNrPos(blockNr);
      dynamic_cast<Dnode*>(destination)->addNode(file);
    } else {
      ret = -2; // no empty blocks left
    }
  }
	
	return ret;
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
		else {
			theDir += dir[i];
    }
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
			returnNode = nullptr;
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

int FileSystem::format() {
  int firstEmptyBlock = this->getFirstEmptyBlockNr();

  if (firstEmptyBlock == 1) { // fs is already empty
    this->initFileSystem();
  } else { // empty the fs
    //emptyTree(this->mRoot);
    delete this->mRoot;

    initFileSystem();
  }
  
  return 1; // implement proper return value
}

void FileSystem::initFileSystem() {
    this->mRoot = new Dnode();
    this->mWalker = Walker(this->mRoot, nullptr);

    for (int i = 0; i < this->BLOCK_ARRAY_SIZE; i++) {
      this->mBlockNrs[i] = false;
    }
}

void FileSystem::emptyTree(Dnode* node) {
  delete node;
}

void FileSystem::setBlockNrPos(int idx) {
  this->mBlockNrs[idx] = true;
}

void FileSystem::deleteBlockNrPos(int idx) {
  this->mBlockNrs[idx] = false;
}

bool FileSystem::getBlockNrStatus(int idx) {
  return this->mBlockNrs[idx];
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

int FileSystem::copyFile(std::string file, std::string newFilePath)
{
	int exitStatus = -1;
	
	// TODO: Place tempnode on the position we want the node. 
	if (newFilePath == "")
	{
		exitStatus = -3;	
	}	
	else
	{

		std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 

		for(unsigned int i = 0; i < files.size(); i++)
		{
			if(dynamic_cast<Fnode*>(files[i]) && file == files[i]->getName())
			{
				// Not so DRY, COPY&PASTED most FROM createFile-function. maybe baby make function?
				std::string tmp;
				tmp.reserve(512);
				tmp = dynamic_cast<Fnode*>(files[i])->getData();	
				int blockNr = this->getFirstEmptyBlockNr();
    
				if (blockNr != -1) { // no empty blocks left
					Fnode* file = new Fnode(tmp, mWalker.getLookingAt()->getPath(), newFilePath, mWalker.getLookingAt(), blockNr);	

					this->setBlockNrPos(blockNr);
					dynamic_cast<Dnode*>(mWalker.getLookingAt())->addNode(file);
					exitStatus = 1;
				} else {
					//std::cout << "No empty blocks left" << std::endl; // for debug
					exitStatus = -2;
				}	
			}
			
		}	
			
	}

	return exitStatus;
}

std::vector<std::string> FileSystem::seperateDir(const std::string & dir)
{
	std::vector<std::string> returnVector;
	returnVector.resize(2);
	if (dir.rfind("/") != -1)
	{
		returnVector[1] = dir.substr(dir.rfind("/") + 1);
		returnVector[0] = dir.substr(0, dir.rfind("/"));
	}
	else
	{
		returnVector[1] = dir;
		returnVector[0] = "";
	}

	return returnVector;
}

