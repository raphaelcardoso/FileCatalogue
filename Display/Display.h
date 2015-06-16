#ifndef DISPLAY_H
#define DISPLAY_H 

/////////////////////////////////////////////////////////////////////////////
// Display.h - Support display operations								   //
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
* This Package displays the files and directories information as called
* by the executive package.
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

#include <iostream>
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"
#include<vector>
using namespace std;

class Display{
public:

	void displayHandle(vector<string> options_, int files_, int directories_, map <string, list<DataStore::PathIter>> mapVal,
		vector<string> files, DataStore dataStore);

	void displayIfOptionsEmpty(int files, int directories);

	void displayduplicates(map <string, list<DataStore::PathIter>> val);

	void displayFileCatalog(map <string, list<DataStore::PathIter>> val);

	void Displayfiles(vector<string> files);

};

#endif