#include <iostream>
#include <sstream>
#include "filesystem.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","createImage","restoreImage",
    "rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
std::string help();

int main(void) {
	
	FileSystem fs = FileSystem();
	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@";    // Change this if you want another user to be displayed	
	int exitStatus = 0;

    bool bRun = true;

    do {
		std::string currentDir = fs.printCurrentWorkingDirectory();    // current directory, used for output
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);
		std::string commandArr[MAXCOMMANDS];
        
		int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {
			
			//std::cout << commandArr[1] << std::endl; //for debugging only!
            
			int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

            case 0: // quit
                bRun = false;
                std::cout << "Exiting\n";
                break;
            case 1: // format
                fs.format();
                break;
            case 2: // ls
                std::cout << "Listing directory" << std::endl; 
				        std::cout << fs.listDir(commandArr[1]);
                break;
            case 3: // create
				        fs.createFile(commandArr[1]);
                break;
            case 4: // cat
                std::cout << fs.printContents(commandArr[1]) << std::endl;
                break;
            case 5: // createImage
                fs.createImage();
                break;
            case 6: // restoreImage
                break;
            case 7: // rm
                fs.removeFile(commandArr[1]);
                break;
            case 8: // cp
				exitStatus = fs.copyFile(commandArr[1], commandArr[2]);
				if (exitStatus == -1)
				{
					std::cout << "No such file: " + commandArr[1] << std::endl;
				}
				else if (exitStatus == -2)
				{
					std::cout << "Disk is full." << std::endl;
				}
				else if (exitStatus == -3)
				{
					std::cout << "cp: missing destination file operand after " + commandArr[1] << std::endl;
				}
                break;
            case 9: // append
                break;
            case 10: // mv
                break;
            case 11: // mkdir 
                fs.createFolder(commandArr[1]);
                break;
            case 12: // cd
				fs.goToFolder(commandArr[1]);
                break;
            case 13: // pwd
				std::cout << '/' + fs.printCurrentWorkingDirectory() + '\n';
                break;
            case 14: // help
                std::cout << help() << std::endl;
                break;
            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}
