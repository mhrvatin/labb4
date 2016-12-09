#include "filesystem.h"


FileSystem::FileSystem() {
  this->mMemBlockDevice = MemBlockDevice(this->BLOCK_ARRAY_SIZE);
  this->format();
}

FileSystem::~FileSystem() {
  delete this->mRoot;
}
void FileSystem::createFolder(std::string folderName) {
  std::vector<std::string> destFile = seperateDir(folderName); 
  Bnode* destination;
  
  if (destFile[0] != "") {
    destination = findDir(destFile[0]);
   
    if(destination == nullptr) {
      return;
    }
  } else {
	  destination = mWalker.getLookingAt();
  }


  dynamic_cast<Dnode*>(destination)->addNode(new Dnode(destination->getPath() + 
			destFile[1] + "/", destFile[1], destination));
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
  int ret = -1;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 
  
  for (unsigned int i = 0; i < files.size() && ret == -1; i++) {
    if (files.at(i)->getName() == fileName) {
			if(dynamic_cast<Fnode*>(files.at(i)))
			{			
        ret = 1;
        Fnode* fileToDelete = dynamic_cast<Fnode*>(files.at(i));

				dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->removeNode(i);
        this->deleteBlockNrPos(fileToDelete->getBlockNr()); // set file's block position as empty
			}
		}
	}

  return ret;
}

std::string FileSystem::listDir(std::string dir) { 
	Bnode* cdDir;
	std::string listDirs = "";

	if(dir == "") {
		cdDir = mWalker.getLookingAt();	
	} else {
		cdDir = findDir(dir);
	}
	
	if (cdDir != nullptr) {
		std::vector<Bnode*> files = dynamic_cast<Dnode*>(cdDir)->getFiles(); 
		for (unsigned int i = 0; i < files.size(); i++) {
			listDirs += files.at(i)->getName() + '\n';
		}
	} else {
		listDirs = "Couldn't find folder " + dir + '\n';
	}	


	return listDirs;
}

int FileSystem::createFile(std::string fileName) {
  int ret = -1;	
  std::vector<std::string> destFile = seperateDir(fileName);
  Bnode* destination;
  
  if (destFile[0] != "") {
	  destination = findDir(destFile[0]);

	  if(destination == nullptr) {
		  return ret;
	  }
  } else {
	  destination = mWalker.getLookingAt();
  }

 if (fileName.length() > 0) {
    ret = 1;
    std::string tmp;
    int blockNr = this->getFirstEmptyBlockNr();

    tmp = "tmp-value"; // TODO: user should be able to input text in file by themself 
    //std::cin >> tmp;
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
  std::string loggedInUser = getlogin();
  std::string path = "/home/" + loggedInUser + "/labb4_filesystem_image.ser";
  std::cout << loggedInUser << std::endl; // print logged in user

  std::ofstream outputFilestream(path);
  boost::archive::text_oarchive outputArchive(outputFilestream);
  outputArchive & this->mRoot;

  return 1; // fix proper return value
}

int FileSystem::goToFolder(std::string dir) {
	int ret = -1;
	Bnode* cdNode = findDir(dir);

	if (cdNode != nullptr) {
    ret = 1;

		mWalker.setLookingAt(cdNode);
		mWalker.setPrev(cdNode->getDotDot());
	}

	return ret;
}

Bnode* FileSystem::findDir(std::string dir) {
	std::string theDir = "";
	std::vector<std::string> dirs = std::vector<std::string>();

	for(unsigned int i = 0; i < dir.size(); i++) {
		
		if (dir[i] == '/' || i == dir.size()-1) {
			if(i == dir.size()-1) {
				theDir += dir[i];
			}

			dirs.push_back(theDir);
			theDir = "";
		} else {
			theDir += dir[i];
    }
	}

	return traverseTree(dirs, 0, mWalker.getLookingAt());	
}


Bnode* FileSystem::traverseTree(std::vector<std::string> dir, int size, Bnode* theNode) {
	Bnode* returnNode = theNode;
	// std::cout << "Size of dir.size(): " << dir.size() << std::endl << "Size of size: " << size << std::endl;
	
	if(size == dir.size()) {
		// std::cout << "REACHED BASE"; // DEBUGG ONLY
		return returnNode;
	} else {
		if (dir[size] == "..") {
			if (theNode->getDotDot() != nullptr) {	
				//std::cout << "Going back one dir" + '\n'; FOR DEBUGGING ONLY	
				returnNode = theNode->getDotDot();
			}	
		} else {
			//std::cout << dir[size] << std::endl; # FOR DEBUGGING ONLY
			std::vector<Bnode*> files = dynamic_cast<Dnode*>(returnNode)->getFiles();
			returnNode = nullptr;
			for(unsigned int i = 0; i < files.size(); i++) {	
			
				if (dynamic_cast<Dnode*>(files.at(i))) {	
					if(dir[size] == files.at(i)->getName()) {
						//std::cout << " CHANGING DIRECTORY " + dir[size] + '\n'; //FOR DEBUGGING ONLY
						returnNode = files.at(i);
						break;
					} else if (i == files.size()-1) {	
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
  int firstEmptyBlock = this->getFirstEmptyBlockNr(),
      ret = -1;

  if (firstEmptyBlock == 1) { // fs is already empty
    this->initFileSystem();
    ret = 1; // filesystem created from scratch
  } else { // empty the fs
    delete this->mRoot;

    initFileSystem();
    ret = 2; // filesystem erased and formatted
  }
  
  return ret; // implement proper return value
}

void FileSystem::initFileSystem() {
    this->mRoot = new Dnode();
    this->mWalker = Walker(this->mRoot, nullptr);

    for (int i = 0; i < this->BLOCK_ARRAY_SIZE; i++) {
      this->mBlockNrs[i] = false;
    }
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

int FileSystem::copyFile(std::string file, std::string newFilePath) {
	int exitStatus = -1;
	
	if (newFilePath == "") {
		exitStatus = -3;
		return exitStatus;	
	}
	
	std::vector<std::string> destFile = seperateDir(newFilePath);
	Bnode* destination;
  
	if (destFile[0] != "") {
		destination = findDir(destFile[0]);
	
		if(destination == nullptr) {
			exitStatus = -4;
			return exitStatus;
		}
	} else {
		destination = mWalker.getLookingAt();
	}

	std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles(); 

	for(unsigned int i = 0; i < files.size(); i++) {
		if(dynamic_cast<Fnode*>(files[i]) && file == files[i]->getName()) {
				
			std::string tmp;
			tmp.reserve(512);
			tmp = dynamic_cast<Fnode*>(files[i])->getData();	
			int blockNr = this->getFirstEmptyBlockNr();
    
			if (blockNr != -1) { // no empty blocks left
				Fnode* file = new Fnode(dynamic_cast<Fnode*>(files[i])->getData(),
            destination->getPath(), destFile[1], destination, blockNr);	

				this->setBlockNrPos(blockNr);
				dynamic_cast<Dnode*>(destination)->addNode(file);
				exitStatus = 1;
				 
				if (mMemBlockDevice.writeBlock(blockNr, tmp) != 1) {
					exitStatus = -5; // generic error
				}


			} else {
				//std::cout << "No empty blocks left" << std::endl; // for debug
				exitStatus = -2;
			}	
		}
			
	}	


	return exitStatus;
}

std::vector<std::string> FileSystem::seperateDir(const std::string & dir) {
	std::vector<std::string> returnVector;
	returnVector.resize(2);
	
  if (dir.rfind("/") != -1) {
		returnVector[1] = dir.substr(dir.rfind("/") + 1);
		returnVector[0] = dir.substr(0, dir.rfind("/"));
	} else {
		returnVector[1] = dir;
		returnVector[0] = "";
	}

	return returnVector;
}
