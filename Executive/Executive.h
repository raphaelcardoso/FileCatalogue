#ifndef EXEC_H
#define EXEC_H 

/////////////////////////////////////////////////////////////////////////////
// Executive.h - Support excutive package operations to call other packages//
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
* This Package acts as communication path between all other packages such
* data store, file management etc..,
*
*/
/* Required Files:
*   FileManager.h, DataStore.h, Display.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 10 Feb 2015
* - first release
*/ 

#include <iostream>
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"
#include "../FileMgr/FileSystem.h"
#include "../Display/Display.h"
#include<vector>
#include<regex>

class  Executive
{
public:
	
	string processArgumentPath(char *  argv[], int argc);
	
	vector<string> processArgumentOptions(char * argv[], int argc); 
	
	vector<string> processArgumentsPattern(char * argv[], int argc); 

	void Executive::userInput(int flag, DataStore dataStore);

	bool Executive::checkQuit(string inp); 
	
};
#endif
