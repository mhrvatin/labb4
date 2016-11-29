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
  dynamic_cast<Dnode*>(mWalker.getLookingAt())->addNode(folder);

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
	dynamic_cast<Dnode*>(mWalker.getLookingAt())->addNode(file);
	
	return 1; // Fix proper return-value.
}

int FileSystem::goToFolder(std::string dir)
{
	//TODO: SET MWALKER ON PROPPER DIR.
	std::vector<Bnode*> files = dynamic_cast<Dnode*>(this->mWalker.getLookingAt())->getFiles();

	for(unsigned int i = 0; i < files.size(); i++)
	{
		if(dir == files.at(i)->getName())
		{
			if (dynamic_cast<Dnode*>(files.at(i)))
			{
				std::cout << " CHANGING DIRECTORY " + dir + '\n';
				mWalker.setLookingAt(files.at(i), mWalker.getLookingAt());
			}
			else
			{
				std::cout << "cd: " + dir + ": Not a directory" + '\n';
			}
		}
	}

	return 1; // Fix proper return-value
} 
