/////////////////////////////////////////////////////////////////////////////
// FileManager.cpp - Support file management operations                    //
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


#include "FileMgr.h"
#include "../DataStore/DataStore.h"
#include <iostream>
using namespace std;

//--------------<File Manager Constructor>----------------

FileManager::FileManager(vector<string> options, vector<string> pattern) :
patterns_(pattern)
{

	if (pattern.empty())
		patterns_.push_back("*.*");

	for (unsigned int i = 0; i < options.size(); i++)
	{
		string search = options[i];
		if (search.compare("/s") == 0)
		{
			switchS = 1;
			cout << "--------------------------------------------\n";
			cout << "\nRecursive Directory Search\n";
			cout << "--------------------------------------------\n";
		}
	}
}

//--------------<returns number of files>----------------

unsigned int FileManager::number_of_files()
{
	return files_count;
}

//--------------<returns number of directories>----------------

unsigned int FileManager::number_of_dir()
{
	return directory_count;
}

//--------------<search for particular file>----------------

void FileManager::search(const std::string& path, DataStore& ds)
{
	for (auto patt : patterns_)
	{
		std::vector<std::string> files = FileSystem::Directory::getFiles(path, patt);
		files_count += files.size();
		std::string path_ = FileSystem::Path::getFullFileSpec(path);
		ds.save(path_);
		for each (std::string file in files)
		{
			ds.save(file, path_);
		}

		if (switchS)
		{
			vector<std::string> dirs = FileSystem::Directory::getDirectories(path, "*.*");
			directory_count += (dirs.size() - 2);

			for (unsigned int i = 2; i < dirs.size(); i++)
			{
				string s = path_ + "\\" + dirs[i];
				search(s, ds);
			}
		}
	}
}

//----< test stub >--------------------------------------------------------

#ifdef TEST_FILEMGR


int main()
{
	DataStore dataStore;
	vector<string> input_a;
	vector<string>input_b;
	input_a.push_back("\\s");
	input_b.push_back("*.*");
	FileManager fileManager(input_a, input_b);
	fileManager.search(".", dataStore);
	map <string, list<DataStore::PathIter>> val = dataStore.dispMap();

	unsigned int i = fileManager.number_of_dir();
	unsigned int j = fileManager.number_of_files();

	std::cout << "\n Number of directories is : " << i << "\n";
	std::cout << "\n Number of files is : " << j << "\n";
	return 0;
}
#endif
