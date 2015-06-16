/////////////////////////////////////////////////////////////////////////////
// Executive.cpp - Support executive package to call other packages        //
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
#include "Executive.h"
#include "../FileMgr/FileMgr.h"
#include "../DataStore/DataStore.h"
#include "../Display/Display.h"
#include "../FileMgr/FileSystem.h"
#include <locale>  
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <cctype>      
#include <functional> 
using namespace std;


//---------------<processes the options given by the user>-------------------------

vector<string> Executive::processArgumentOptions(char * argv[], int argc)
{
	vector<string> option;
	int temp = 1;

	for (int i = 1; i < argc; i++)
	{
		string j = argv[i];
		if (j.compare("/d") == 0 || j.compare("/s") == 0)
		{

			if (option.size() != 0){
				for (size_t q = 0; q < option.size(); q++)
				{
					if (option[q] == j)
					{
						temp = 0;
						break;
					}
				}
				if (temp)
					option.push_back(argv[i]);
			}
			else
				option.push_back(argv[i]);
		}
		//string s = argv[i];
		if (j.find("/f") != -1)
		{
			if (option.size() != 0){
				for (size_t q = 0; q < option.size(); q++)
				{
					if (option[q] == j)
					{
						temp = 0;
						break;
					}
				}
				if (temp)
					option.push_back(argv[i]);
			}
			else
				option.push_back(argv[i]);
		}
	}

	return option;
}

//-------------------<processes the patterns given by the user>-------------------------------

vector<string> Executive::processArgumentsPattern(char * argv[], int argc)
{

	vector<string> pattern;

	regex r("[A-Za-z\\*]+\\.[A-Za-z\\*]+$");
	for (int i = 1; i < argc; ++i)
	{
		if (regex_match(argv[i], r))
			pattern.push_back(argv[i]);
	}
	return pattern;
}


//--------------< the program starts from this point>----------------

int main(int argc, char *  argv[])
{
	DataStore dataStore;
	Display display;
	string path;
	vector<string>options;
	vector<string>pattern;
	vector<string> files;
	Executive executive;

	if (argc == 1)
		path = ".";
	else
	{
		path = argv[1];
		std::string pathTest = FileSystem::Path::getFullFileSpec(path);
		DWORD ftyp = GetFileAttributesA(pathTest.c_str());						//checks if user has provided path or not
		if (ftyp == INVALID_FILE_ATTRIBUTES)
			path = ".";
	}
	pattern = executive.processArgumentsPattern(argv, argc);
	options = executive.processArgumentOptions(argv, argc);

	if (pattern.size() == 0)
		pattern.push_back("*.*");
	FileManager fileManager(options, pattern);
	fileManager.search(path, dataStore);
	map <string, list<DataStore::PathIter>> mapVal = dataStore.dispMap();
	int number_of_directories = fileManager.number_of_dir();
	int number_of_file = fileManager.number_of_files();

	display.displayHandle(options, number_of_file, number_of_directories, mapVal, files, dataStore);

	int flag = 1;

	while (flag)
	{
		//options.clear(); 
		pattern.clear();
		dataStore.clear();
		cin.clear();
		fflush(stdin);

		cout << endl << "================================================================================";
		cout << "================================================================================" << endl;
		cout << "**************User Inputs**************" << endl;
		cout << endl << "================================================================================";
		cout << "================================================================================" << endl;
		cout << endl << "Please enter the text you want to search OR press enter to exit" << endl << endl;

		string input = "";
		//cin>> input;
		input = cin.get(); 

		if (input == "\n") //.empty())
		{
			cout << "\n Exiting as no text is entered!!" << endl;
			break;
		}

		cout << "\n Please enter file pattern(s) in which text needs to be searched" << endl;
		cin.clear();
		fflush(stdin);

		string newPattern = "";
		getline(cin,newPattern);

		istringstream iss(newPattern);
		vector<string> tokens{ istream_iterator < string > {iss},
			istream_iterator < string > {} };

		regex r("[A-Za-z\\*]+\\.[A-Za-z\\*]+$");
		for (string tok : tokens)
		{
			if (regex_match(tok, r))
				pattern.push_back(tok);
		}


		if (pattern.size() == 0)
			pattern.push_back("*.*");

		string a = "/f<" + input + ">";


		//options.push_back("/d"); 

		std::vector<string>::iterator iter = options.begin();

		while (iter != options.end())
		{
			if (*iter == a)
				iter = options.erase(iter);
			else
				iter++;
		}

		options.push_back(a);

		map<string, int> m;
		for (auto & i : options)
			m[i]++;
		options.clear();
		for (auto & i : m)
		if (i.second == 1)
			options.push_back(i.first);


		FileManager fileManager(options, pattern);
		fileManager.search(path, dataStore);
		map <string, list<DataStore::PathIter>> mapVal = dataStore.dispMap();
		int number_of_directories = fileManager.number_of_dir();
		int number_of_file = fileManager.number_of_files();

		display.displayHandle(options, number_of_file, number_of_directories, mapVal, files, dataStore);

		options.pop_back();

		cout << "\n Press Enter to Exit and Press spacebar to Continue (Search an other text) \n";
		//cin >> flag; 

		string case_ = ""; 
		case_ = cin.get();

		if (case_ == "\n") //atoi(case_.c_str())) // "")
		{
			flag = 0; 
		}
	}

	system("pause");
	return 0;
}