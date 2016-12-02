#include "filesystem.h"

FileSystem::FileSystem() {
  this->mMemBlockDevice = MemBlockDevice(this->BLOCK_ARRAY_SIZE);
  this->format();
}

FileSystem::~FileSystem() {
  delete mRoot;
}

int FileSystem::createFolder(std::string folderName) {
  // TODO: don't execute unless a valid paramater is given
  Dnode* folder = new Dnode(mWalker.getCwd(), folderName, mWalker.getLookingAt());
  mRoot->addNode(folder);

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

  return contents; // implement proper return value
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

int FileSystem::createFile(std::string fileName) {
  int ret = -1;

  if (fileName.length() > 0) {
    ret = 1;
    std::string tmp;
    int blockNr = this->getFirstEmptyBlockNr();

    tmp = "test test"; // TODO: user should be able to input text in file by themself 
    tmp.resize(512);
      
    if (blockNr != -1) { // empty blocks are still available
      Fnode* file = new Fnode(tmp, mWalker.getCwd(), fileName, mWalker.getLookingAt(), blockNr);	
      std::string tmp = file->getData();
      std::cout << "file->getData() size:" << tmp.size() << "." << std::endl;
      
      if (mMemBlockDevice.writeBlock(blockNr, file->getData()) == 1) {
        std::cout << "filesystem::createFile: block written!" << std::endl; // for debuging
      } else {
        std::cout << "filesystem::createFile: an error occured" << std::endl; // for debuging
      }

      this->setBlockNrPos(blockNr);
      mRoot->addNode(file);
    } else {
      std::cout << "No empty blocks left" << std::endl; // for debuging
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

int FileSystem::format() {
  int firstEmptyBlock = this->getFirstEmptyBlockNr();
  if (firstEmptyBlock != -1) { // fs is already empty
    this->mRoot = new Dnode();
    this->mWalker = Walker(this->mRoot, nullptr, "/");

    for (int i = 0; i < this->BLOCK_ARRAY_SIZE; i++) {
      this->blockNrs[i] = false;
    }
  } else { // empty the fs

  }
  
  return 1; // implement proper return value
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
