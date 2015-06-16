#ifndef FILEMGR_H
#define FILEMGR_H

/////////////////////////////////////////////////////////////////////////////
// FileManager.h - Support file management operations                      //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell 15 i15547, Core i5, Windows 8 SP1                     //
// Application: OOD Project 1, 2015                                        //
// Author:      Raghavendra Manjegowda, Syracuse University                //
//              (315) 925-9043, rmanjego@syr.edu                           //
/////////////////////////////////////////////////////////////////////////////
/*
* Module Operations:
* ------------------
* This Package handles file management related functions such as searching
* files and directories and stores the information by calling data store
* package.
*
*/
/* Required Files:
*   FileManager.h, DataStore.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 10 Feb 2015
* - first release
*/

// FileMgr.h -    ...

#include "FileSystem.h"
#include "../DataStore/DataStore.h"
#include <iostream>
using namespace std;

class FileManager
{
public:
	using iterator = DataStore::iterator;
	using patterns = std::vector<std::string>;

	FileManager(vector<string> options, vector<string> pattern);
	unsigned int number_of_files();
	unsigned int number_of_dir();
	void search(const std::string& path, DataStore& ds);

private:
	patterns patterns_;

	int switchS = 0;

	unsigned int directory_count = 1;
	unsigned int files_count = 0;

};
#endif
