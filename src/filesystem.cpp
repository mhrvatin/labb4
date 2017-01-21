#include "filesystem.h"

FileSystem::FileSystem() {
  this->mMemBlockDevice = MemBlockDevice(this->BLOCK_ARRAY_SIZE);
  this->initFileSystem();
}

FileSystem::~FileSystem() {
  delete this->mRoot;
}
void FileSystem::createFolder(std::string folderName) {
  std::vector<std::string> destFile = separateDir(folderName); 
  Dnode* destination;
  
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
  
  std::vector<std::string> destFile = separateDir(fileName);
  Bnode* destination;
  std::string contents = "No such file or directory";
  
  if (destFile[0] != "")
  {
	destination = findDir(destFile[0]);

	if (destination == nullptr)
	{
		return contents;
	}	
  }
  else
  {
	destination = mWalker.getLookingAt();
  }


  bool hit = false;
  std::vector<Bnode*> files = dynamic_cast<Dnode*>(destination)->getFiles(); 
  
  for (unsigned int i = 0; i < files.size() && !hit; i++) {
    if (dynamic_cast<Fnode*>(files.at(i)) && files.at(i)->getName() == destFile[1]) {
      hit = true;
      Fnode* foundFile = dynamic_cast<Fnode*>(files.at(i));

	 // std::cout << "Found file blocknr: " << foundFile->getBlockNr() << std::endl;
      Block block = this->mMemBlockDevice.readBlock(foundFile->getBlockNr());
      contents = block.toString();
	  //contents = foundFile->getData();
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
  std::vector<std::string> destFile = separateDir(fileName);
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

    std::cin >> tmp;
	std::cin.ignore();
    tmp.resize(512);

    if (blockNr != -1) { // empty blocks are still available
      Fnode* file = new Fnode(tmp, destination->getPath(), destFile[1], blockNr);	
	  ret = this->writeFileDataToBlock(file, blockNr);
      dynamic_cast<Dnode*>(destination)->addNode(file);
    } else {
      ret = -2; // no empty blocks left
    }
  }
	
	return ret;
}


void FileSystem::createImage() {
  std::string loggedInUser = getlogin();
  std::string path = "/home/" + loggedInUser + "/labb4_filesystem_image.ser";

  std::ofstream ofs(path);
  boost::archive::text_oarchive oa(ofs);
  oa & this->mRoot;
}

void FileSystem::restoreImage() {
  std::string loggedInUser = getlogin();
  std::string path = "/home/" + loggedInUser + "/labb4_filesystem_image.ser";

  std::ifstream ifs(path);
  boost::archive::text_iarchive ia(ifs);
  this->format();
  ia & this->mRoot;
  this->mWalker.setLookingAt(this->mRoot);
  this->restoreFileData(mRoot);
}

int FileSystem::goToFolder(std::string dir) {
	int ret = -1;
	Dnode* cdNode = findDir(dir);

	if (cdNode != nullptr) {
    ret = 1;

		mWalker.setLookingAt(cdNode);
		mWalker.setPrev(cdNode->getDotDot());
	}

	return ret;
}

Dnode* FileSystem::findDir(std::string dir) {
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


Dnode* FileSystem::traverseTree(std::vector<std::string> dir, int size, Dnode* theNode) {
	Dnode* returnNode = theNode;
	
	if(size == dir.size()) {
		return returnNode;
	} else {
		if (dir[size] == "..") {
			if (theNode->getDotDot() != nullptr) {	
				returnNode = theNode->getDotDot();
			}	
		} else {
			std::vector<Bnode*> files = dynamic_cast<Dnode*>(returnNode)->getFiles();
			returnNode = nullptr;

			for(unsigned int i = 0; i < files.size(); i++) {	
				if (dynamic_cast<Dnode*>(files.at(i))) {	
					if(dir[size] == files.at(i)->getName()) {
						returnNode = dynamic_cast<Dnode*>(files.at(i));
						break;
					} else if (i == files.size()-1) {	
						size = dir.size()-1;	
						returnNode = nullptr;
					}
				}
			}
			
		}

	  return traverseTree(dir, size+1, returnNode);	
	}
}

void FileSystem::format() {
  delete this->mRoot;

  initFileSystem();
}

void FileSystem::initFileSystem() {
	
	this->mRoot = new Dnode();
    this->mWalker.setLookingAt(this->mRoot); 

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
	
	std::vector<std::string> sourceFile = separateDir(file);
	std::vector<std::string> destFile = separateDir(newFilePath);
	Bnode* destination;
	Bnode* source;	
	
  
	if (sourceFile[0] != "")
	{
		source = findDir(sourceFile[0]);

		if (source == nullptr)
		{
			exitStatus = -4;
			return exitStatus;
		}
	} else {
		source = mWalker.getLookingAt();
	}

	if (destFile[0] != "") {
		destination = findDir(destFile[0]);
	
		if(destination == nullptr) {
			exitStatus = -4;
			return exitStatus;
		}
	} else {
		destination = mWalker.getLookingAt();
	}

	std::vector<Bnode*> files = dynamic_cast<Dnode*>(source)->getFiles(); 

	for(unsigned int i = 0; i < files.size(); i++) {
		if(dynamic_cast<Fnode*>(files[i]) && sourceFile[1] == files[i]->getName()) {
				
			std::string tmp;
			tmp.reserve(512);
			tmp = dynamic_cast<Fnode*>(files[i])->getData();	
			int blockNr = this->getFirstEmptyBlockNr();
    
			if (blockNr != -1) { // no empty blocks left
				Fnode* file = new Fnode(dynamic_cast<Fnode*>(files[i])->getData(),
            destination->getPath(), destFile[1], blockNr);	

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

std::vector<std::string> FileSystem::separateDir(const std::string & dir) {
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

int FileSystem::writeFileDataToBlock(Fnode* file, int blockNr)
{
	int ret = 1;
      std::string tmp = file->getData();
       
      if (mMemBlockDevice.writeBlock(blockNr, file->getData()) != 1) {
        ret = -1; // generic error
      }

	 file->setBlockNr(blockNr);
     this->setBlockNrPos(blockNr);
	return ret;
}

void FileSystem::restoreFileData(Bnode* atNode)
{

	std::vector<Bnode*> theVector = dynamic_cast<Dnode*>(atNode)->getFiles();
	
	for (unsigned int i = 0; i < theVector.size(); i++)
	{
	
		if (dynamic_cast<Fnode*>(theVector.at(i)))
		{
			int blockNr = this->getFirstEmptyBlockNr();
			//std::cout << "Restore data to " << theVector.at(i)->getName() << std::endl;
			//std::cout << "Data to restore " << dynamic_cast<Fnode*>(theVector.at(i))->getData() << std::endl;
			//std::cout << "Blocknr: " << blockNr << std::endl;
			this->writeFileDataToBlock(dynamic_cast<Fnode*>(theVector.at(i)), blockNr);		
	
		}
		else if (dynamic_cast<Dnode*>(theVector.at(i)))
		{
			//std::cout << "Hittar en mapp och kollar på den" << std::endl;
			//std::cout << "Mappnamn: " << theVector.at(i)->getPath() << std::endl; 
			this->restoreFileData(theVector.at(i));	
		}	
	}

}
