#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <algorithm> // writing/reading vector to/from file
#include <fstream>
#include <iostream>  // writing/reading vector to/from file
#include <iterator>  // writing/reading vector to/from file

#include <unistd.h>    // getting userid

#include "memblockdevice.h"
#include "walker.h"
#include "bnode.h"
#include "dnode.h"
#include "fnode.h"

class FileSystem
{
public:
    static const int BLOCK_ARRAY_SIZE = 250;
private:
    MemBlockDevice mMemBlockDevice;
    // Here you can add your own data structures
    
    Dnode* mRoot;
    Walker mWalker;
    bool blockNrs[BLOCK_ARRAY_SIZE];
public:

    FileSystem();
    ~FileSystem();
	  
    Bnode* findDir(std::string dir);
	  Bnode* traverseTree(std::vector<std::string> dir, int size, Bnode* theNode);

    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
    int createFile(std::string fileName);

    /* Creates a folder in the filesystem */
    int createFolder(std::string folderName);

    // gets the contents of the file
    std::string printContents(std::string fileName);

    // print out current working directory
    int printCurrentWorkingDirectory();

    /* Removes a file in the filesystem */
    int removeFile(std::string fileName);

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    // Copy file
    int copyFile(std::string file, std::string newFilePath = "");

    /* Function will move the current location to a specified location in the filesystem */
    int goToFolder(std::string dir);

    /* This function will get all the files and folders in the specified folder */
    std::string listDir(std::string dir);

    // Writes the virtual file system to a file on the actual file system
    int createImage();

    // formats the file system
    int format();

    void setBlockNrPos(int idx);
    void deleteBlockNrPos(int idx);
    bool getBlockNrStatus(int idx);
    int getFirstEmptyBlockNr();
};

#endif // FILESYSTEM_H
