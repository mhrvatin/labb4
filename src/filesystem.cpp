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
