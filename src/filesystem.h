#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "memblockdevice.h"
#include "walker.h"
#include "bnode.h"
#include "dnode.h"
#include "fnode.h"

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
    Dnode* mRoot;
    Walker mWalker;
public:
    FileSystem();
    ~FileSystem();

    /* These commands needs to implemented
     *
     * However, you are free to change the parameterlist and specify your own returntype for each function below.
     */

    /* This function creates a file in the filesystem */
    int createFile(std::string fileName);

    /* Creates a folder in the filesystem */
    int createFolder(std::string folderName);

    // gets the contents of the file
    int printContents(std::string fileName);

    /* Removes a file in the filesystem */
    // removeFile(...);

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    /* Function will move the current location to a specified location in the filesystem */
    // goToFolder(...);

    /* This function will get all the files and folders in the specified folder */
    std::string listDir(std::string dir);

    /* Add your own member-functions if needed */
};

#endif // FILESYSTEM_H
