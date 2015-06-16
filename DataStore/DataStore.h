#ifndef DATASTORE_H
#define DATASTORE_H

/////////////////////////////////////////////////////////////////////////////
// DataStore.h - Support data store operations							   //
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
* This Package stores files search and directory search results into
* data save containers defined in data store package such as map and set
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

// DataStore.h - ....
#include "../FileMgr/FileSystem.h"
#include "../DataStore/DataStore.h"

#pragma once 
using namespace std;
#include <vector>
#include<set>
#include<list>
#include<map>
#include<iostream>
class DataStore
{
public:

	using Path = string;
	using Paths = set < Path >;
	using PathIter = Paths::iterator;
	using ListOfIters = list< PathIter >;
	using File = string;
	using Store = map < File, ListOfIters >;
	using iterator = Store::iterator;

	void DataStore::save(const std::string& filespec);

	void DataStore::save(const std::string& filename, const std::string& path);

	set < Path >DataStore::dispSet();

	map < File, ListOfIters > DataStore::dispMap();

	void DataStore::clear();

	vector<string> DataStore::text1search(string match);

	iterator begin() { return store.begin(); }
	iterator end() { return store.end(); }


private:
	Store store;
	Paths paths;
	vector<string> file;

};
#endif
