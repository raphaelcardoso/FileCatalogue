/////////////////////////////////////////////////////////////////////////////
// Display.cpp - Support display operations								   //
// ver 1.0                                                                 //
// ----------------------------------------------------------------------- //
// Language:    Visual C++, Visual Studio 2013                             //
// Platform:    Dell 15 i15547, Core i5, Windows 8 SP1                     //
// Application: Demonstration for CSE 687, OOD Project 1, Spring 2015	   //
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

#include "Display.h"

//--------------<displays files accordingly to inputs>----------------

void Display::displayHandle(vector<string> options_, int files_, int directories_, map <string, list<DataStore::PathIter>> mapVal,
	vector<string> files, DataStore dataStore) {

	if (options_.empty()) // Requirement 7
	{
		displayIfOptionsEmpty(files_, directories_);
	}

	for (unsigned int k1 = 0; k1 < options_.size(); k1++) // Requirement 5
	{
		string p = options_[k1];
		if (!p.compare("/d"))
			displayduplicates(mapVal);
		else
			displayFileCatalog(mapVal);
	}

	for (unsigned int k2 = 0; k2 < options_.size(); k2++)
	{
		string p1 = options_[k2];
		if (p1.find("/f<") != -1)
		{
			string s3 = p1.substr(3, p1.length() - 4); 
			cout << "Text being searched is :" << s3; 
			files = dataStore.text1search(s3);
		}
	}

	for (unsigned k3 = 0; k3 < options_.size(); k3++)
	{
		string p1 = options_[k3];
		if (p1.find("/f<") != -1)
		{
			Displayfiles(files);
		}
	}
}

//--------------<display if no options is entered>----------------

void Display::displayIfOptionsEmpty(int files, int directories) {

	cout << " No Options Specified\n";
	cout << "Number of Files Found " << files << "\n";
	cout << "------------------------------------------\n";
	cout << "Number Of Directories Traversed " << directories << "\n";
	cout << "------------------------------------------\n";


}

//--------------<displays duplicate files>----------------

void Display::displayduplicates(map <string, list<DataStore::PathIter>> val) {
	cout << "Displaying Duplicates in the File Catalog if present" << "\n";
	cout << "-----------------------------------------------------------";
	int flag = 1;
	using Store = map < string, list<DataStore::PathIter> >;
	using iterator = Store::iterator;
	for (iterator iter = val.begin(); iter != val.end(); ++iter)
	{

		if (iter->second.size() > 1)
		{
			flag = 0;
			cout << "\n";
			cout << "Duplicate File Name: ";
			cout << iter->first;
			cout << "\nPaths:\n";
			DataStore::ListOfIters listofIter = iter->second;
			for (auto path = listofIter.begin(); path != listofIter.end(); ++path)
			{
				cout << **path << "\n";
			}
			cout << "\n--------------------------------------------------------\n";
		}

	}

	if (flag)
		cout << "\n No duplicate file present\n";

}

//--------------<displays file catalogue, not used as it is not required>----------------

void Display::displayFileCatalog(map <string, list<DataStore::PathIter>> val) {
	cout << "\nDisplay OF Contents in the File Catalog" << "\n";
	cout << "-----------------------------------------------------------";
	using Store = map < string, list<DataStore::PathIter> >;
	using iterator = Store::iterator;
	for (iterator iter = val.begin(); iter != val.end(); ++iter)
	{
	cout << "\nFile Name:" << "                                        ";
	cout << iter->first;
	cout << "\nPaths:\n";

	DataStore::ListOfIters listofIter = iter->second;
	for (auto path = listofIter.begin(); path != listofIter.end(); ++path)
	{
	cout << **path << "\n";

	}
	cout << "\n--------------------------------------------------------\n";
	}
}

//--------------<displays file>----------------

void Display::Displayfiles(vector<string> files) {
	for (unsigned k = 0; k < files.size(); k++)
	{
		cout << "\n Files which match the given Text \n";
		cout << files[k] << "\n";
	}
}

//----< test stub >--------------------------------------------------------

#ifdef TEST_DISPLAY 
void main()
{
	Display D;
	vector<string> files;
	files.push_back("a.txt");
	files.push_back("b.txt");
	D.Displayfiles(files);
}
#endif