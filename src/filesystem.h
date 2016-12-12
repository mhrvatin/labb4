#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <fstream>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include <unistd.h>    // getting userid

#include "memblockdevice.h"
#include "walker.h"
#include "bnode.h"
#include "dnode.h"
#include "fnode.h"

BOOST_CLASS_EXPORT_IMPLEMENT(Fnode);

class FileSystem {
public:
    static const int BLOCK_ARRAY_SIZE = 250;
private:
    MemBlockDevice mMemBlockDevice;
    
    Dnode* mRoot;
    Walker mWalker;
    bool mBlockNrs[BLOCK_ARRAY_SIZE];
public:

    FileSystem();
    ~FileSystem();

    /* Creates a folder in the filesystem */
    void createFolder(std::string folderName);
	  
    // gets the contents of the file
    std::string printContents(std::string fileName);

    // print out current working directory
	  std::string printCurrentWorkingDirectory();

    /* Removes a file in the filesystem */
    int removeFile(std::string fileName);

    /* This function will get all the files and folders in the specified folder */
    std::string listDir(std::string dir);

    /* This function creates a file in the filesystem */
    int createFile(std::string fileName);

    // Writes the virtual file system to a file on the actual file system
    void createImage();

    // Reads a file on the actual file system to create the virtual file system
    void restoreImage();

    /* Function will move the current location to a specified location in the filesystem */
    int goToFolder(std::string dir);

    // Helper function to find the directory in a path
    Dnode* findDir(std::string dir);

    // Helper function to traverse the file tree
	  Dnode* traverseTree(std::vector<std::string> dir, int size, Dnode* theNode);

    // Formats the file system
    void format();

    // Initialize a new file system
    void initFileSystem();

    void setBlockNrPos(int idx);

    void deleteBlockNrPos(int idx);
    
    bool getBlockNrStatus(int idx);

    int getFirstEmptyBlockNr();

    // Copy file
    int copyFile(std::string file, std::string newFilePath = "");

    // Helper function to split a path into path and directory
	  std::vector<std::string> separateDir(const std::string & dir);
};

#endif // FILESYSTEM_H
