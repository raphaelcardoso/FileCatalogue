/////////////////////////////////////////////////////////////////////////////
// DataStore.cpp - Support Data Store operations                           //
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
*   DataStore.h
*
* Maintenance History:
* --------------------
* ver 1.0 : 10 Feb 2015
* - first release
*/

#pragma once
#include "DataStore.h" 
#include <vector>
#include<set>
#include<list>
#include<map>
#include<iostream>

#include <iostream>

using Path = string;
using Paths = set < Path >;
using PathIter = Paths::iterator;
using ListOfIters = list< PathIter >;
using File = string;
using Store = map < File, ListOfIters >;
using iterator = Store::iterator;

//--------------<save file specificaton>----------------

void DataStore::save(const std::string& filespec)
{
	paths.insert(filespec);

}

//--------------<save file name and path (in MAP)>----------------

void DataStore::save(const std::string& filename, const std::string& path)
{
	bool flag = false;
	set<Path> ::iterator i = paths.begin();
	for (i = paths.begin(); i != paths.end(); i++)
	{
		if (path == *i)
		{
			if (store.size() == 0)
			{
				std::list<PathIter> a;
				a.push_back(i);
				store[filename] = a;
			}

			else
			{
				map<File, ListOfIters> ::iterator m = store.begin();
				for (m = store.begin(); m != store.end(); m++)
				{
					if (m->first == filename)
					{
						std::list<PathIter> val = m->second;
						for (auto paths = val.begin(); paths != val.end(); ++paths)
						{
							if (**paths == path)
								return; 
						}
						
						val.push_back(i);
						store[filename] = val;
						flag = true;
						break;
					}
				}
				if (!flag)
				{

					std::list<PathIter> n;
					n.push_back(i);

					store[filename] = n;
				}
			}
		}
	}
}

//--------------<displays set>----------------

set < Path >DataStore::dispSet()
{
	return paths;
}

//--------------<displays map>----------------

map < File, ListOfIters > DataStore::dispMap()
{
	return store;
}

//--------------<clears previous data>----------------

void DataStore::clear(){
	store.clear();
}

//--------------<search's text in particluar file>----------------

vector<string> DataStore::text1search(string match)
{

	for (DataStore::iterator it = store.begin(); it != store.end(); ++it)
	{
		std::string fileName = it->first;
		std::string filePath = **it->second.begin();
		FileSystem::File* myFile = new FileSystem::File(filePath + "//" + fileName);
		myFile->open(FileSystem::File::in);
		std::string contents = myFile->readAll();
		std::size_t found = contents.find(match, 0);
		if (found != std::string::npos)
		{
			file.push_back(fileName);
		}
		myFile->close();
	}
	return file;
}

//----< test stub >--------------------------------------------------------

#ifdef TEST_DATASTORE 

int main()
{
	std::cout << "\n  Testing DataStore";

	DataStore ds;
	ds.save("*.*", ".");
	std::cout << "\n Data Store \n";

	std::string fileText = "Hello"; 

	vector<string> vec; 
	vector<string> vec1; 
	vector<string> vec2; 

	vec.push_back("*.*"); 
	vec1 = ds.text1search(fileText); 

	for (unsigned int i = 0; i < vec1.size(); i++)
	{
		cout << "Matched Files" << "\n";
		cout << vec1[i];
	}


}

#endif
