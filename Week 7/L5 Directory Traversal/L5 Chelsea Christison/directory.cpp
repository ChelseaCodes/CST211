/*************************************************************
* Author:		Chelsea Christison
* Filename:		directory.cpp
* Date Created:	5.17.2017
*
**************************************************************/
#include "directory.h"

static int Tabs = 0; 

Directory::Directory()
{}

Directory::Directory(string rootdirectory)
{
	auto position = 
	rootdirectory.find_last_of(":\\");
	string path = rootdirectory;
	
	node nn;
	nn.path = rootdirectory;
	nn.filename = rootdirectory.erase(0, position+1);	
	m_root = nn; 

	char * dir = new char[1000]; 
	strcpy(dir, path.c_str()); 
	
	fillDirectory(dir, m_root); 
	delete[] dir; 

	traverse = ForwardIterator<node>(&m_root.subdirectories);
}

Directory::Directory(const Directory& copy) : m_root(copy.m_root)
{}

Directory& Directory::operator=(const Directory& rhs)
{
	if(this != &rhs)
	{
		m_root = rhs.m_root; 
	}
	return *this; 
}

Directory::~Directory()
{
}

/************************************************************************
* Purpose: 
*	this function fills the Directory structure. 
*	
* Pre-Conditions:
*	dir -  where directory begins for finding the files
*	directory -	directory from command prompt
*
* Post-Conditions:
*	loads Directory data struct to follow a directory hierarchy 
*	
*************************************************************************/
void Directory::fillDirectory(char* dir, node& directory)
{
	_finddata_t find_buf;
	intptr_t rc;
	char temp[1500] = { 0 };

	//cout << dir << endl;

	strcat(dir, "\\*"); // Specify the search string

	// Find the first file or directory
	rc = _findfirst(dir, &find_buf);

	if (rc == -1L)
	{
		cout << "No \\* files in current directory" << endl;
	}
	else
	{
		do
		{
			// Ignore the . and .. directories
			if (strcmp(find_buf.name, ".") != 0 &&
				strcmp(find_buf.name, "..") != 0 && !(find_buf.attrib & _A_SYSTEM))
			{
				node nn;
				nn.filename = find_buf.name;
				

				strcpy(temp, dir);
				temp[strlen(temp) - 1] = '\0'; // Remove the *
				nn.path = temp;

				// Append new directory name
				strcat(temp, find_buf.name);

				directory.subdirectories.Append(nn); 

				//cout << temp << endl; // Output 

				 // If its a subdirectory, recurse into that directory
				if (find_buf.attrib & _A_SUBDIR)
				{
					//cout << "Making recursive call on: " << temp << endl;
					node * addto = directory.subdirectories.getTail()->getData();

					// Recurse into the subdirectory
					fillDirectory(temp, *addto);
				}
			}
		} while (_findnext(rc, &find_buf) == 0); // Find the next directory or file
		_findclose(rc);
	}
}

/************************************************************************
* Purpose:
*	Determines if a directory given exists in the Directory class
*	and returns a boolean value
*
* Pre-Conditions:
*	dir -  directory path to verify 
*
*************************************************************************/
bool Directory::directoryExists(string dir)
{
	bool found = false; 
	return _recursiveSearch(dir, m_root, found) != nullptr; 
}

/************************************************************************
* Purpose:
*	this function drives listing files by extension and looks in subfiles
*	or not depending on the boolean recursive value. 
*
* Pre-Conditions:
*	dir -  directory to begin search from 
*	recursive - flag indicating to search in subfiles as well
*	extension - extension to look for in files 
*
*************************************************************************/
void Directory::listDirectory(string dir, bool recursive, string extension)
{
	bool found = false;
	bool subdir = false;
	node * directory = _recursiveSearch(dir, m_root, found);
	Tabs = 0; 
	if(directory && recursive)
	{
		cout << "\n__________________________" << endl;
		cout << "All files with extension " << extension.c_str() << " in " << directory->filename.c_str() << ": " << endl;
		cout << "Path: " << directory->path.c_str() << endl << endl;
		cout << "Filename" << setw(76) << "Path" << endl;
		cout << "---------" << setw(80) << "---------" << endl;
		_iterateRecursive(*directory, subdir, extension);
		cout << "___________________________" << endl;
	}
	else
	{
		_iterateAll(*directory, extension); 
	}
}

/************************************************************************
* Purpose:
*	this function drives listing all files in the given directory. If the
*	boolean recursive flag is set, this function will also list all sub
*	directories. 
*
* Pre-Conditions:
*	dir -  directory to begin search from
*	recursive - flag indicating to list subfiles as well
*
*************************************************************************/
void Directory::listDirectory(string dir, bool recursive)
{
	bool found = false; 
	bool subdir = false; 
	node * directory = _recursiveSearch(dir, m_root, found); 
	Tabs = 0; 
	if(directory && recursive)
	{
		cout << "\n__________________________" << endl;
		cout << "All files and subfiles in " << directory->filename.c_str() << ": " << endl;
		cout << "Path: " << directory->path.c_str() << endl << endl;
		cout << "Filename" << endl;
		cout << "---------" << endl;
		_iterateRecursive(*directory, subdir); 
		cout << "___________________________" << endl;
	}
	else
	{
		_iterateAll(*directory); 
	}
}

/************************************************************************
* Purpose:
*	this function calls another function to list all files in the data
*	structure that contain the string passed. 
*
* Pre-Conditions:
*	lookfor - string to find in the filenames in all files in directory
*
*************************************************************************/
void Directory::listDirectory(string lookfor)
{
	cout << "\n__________________________" << endl;
	cout << "Searching for all files with: " << lookfor.c_str() << endl; 
	cout << "Filename" << setw(76) << "Path" << endl;
	cout << "---------" << setw(80) << "---------" << endl;

	_recursiveSearch(lookfor, m_root); 
	cout << "___________________________" << endl;
}

/************************************************************************
* Purpose:
*	this function recursively searches for a node that has the same 
*	directory path of the one passed. Sets a boolean flag if found. 
*
* Pre-Conditions:
*	dir -  directory to search for in data structure
*	directory - directory to begin search from
*	found - boolean flag for found or not found 
*
*************************************************************************/
node* Directory::_recursiveSearch(string dir, node& directory, bool & found)
{
	node * nodefound = nullptr; 

	// search the given directory if there is a match for the searching dir
	if (directory.path.find(dir) != string::npos)
	{
		found = true; 
		nodefound = &directory; 
	}
	
	if(!found)
	{
		ForwardIterator<node> traverse(&directory.subdirectories);

		for (traverse.Reset(); !traverse.IsDone() && !found; traverse.MoveNext())
		{
			node * current = traverse.GetCurrent();
			nodefound = _recursiveSearch(dir, *current, found);
		}

	}
	return nodefound; 
}

/************************************************************************
* Purpose:
*	this function recursively searches for a keyword in all files
*	in the directory. Prints every occurrence of the file where the 
*	keyword appears
*
* Pre-Conditions:
*	keyword - word to search for in directory
*	directory - directory to begin search from
*
*************************************************************************/
void Directory::_recursiveSearch(string keyword, node& directory)
{

	if (directory.subdirectories.getHead())
	{
		ForwardIterator<node> traverse(&directory.subdirectories);

		for (traverse.Reset(); !traverse.IsDone(); traverse.MoveNext())
		{
			string name = traverse.GetCurrent()->filename;
			if (name.find(keyword) != string::npos)
			{
				cout << "- " << setw(78) << left << name.c_str() << right << traverse.GetCurrent()->path.c_str() << endl;
			}
			if (traverse.GetCurrent()->subdirectories.getHead())
			{
				_recursiveSearch(keyword, *traverse.GetCurrent()); 
			}

		}
	}
}

/************************************************************************
* Purpose:
*	this function iterates through the directory given and lists all 
*	files. 
*
* Pre-Conditions:
*	directory - directory to begin listing files from
*
*************************************************************************/
void Directory::_iterateAll(node& directory)
{
	cout << "\n__________________________" << endl;
	cout << "All files in " << directory.filename.c_str() << ": " << endl; 
	cout << "Path: " << directory.path.c_str() << endl << endl; 
	cout << "Filename" << endl; 
	cout << "---------" << endl;

	ForwardIterator<node> traverse(&directory.subdirectories);

	for (traverse.Reset(); !traverse.IsDone(); traverse.MoveNext())
	{
		string name = traverse.GetCurrent()->filename;
		cout << "- " << name.c_str() << endl; 
	}
	cout << "___________________________" << endl; 
}

/************************************************************************
* Purpose:
*	this function iterates through directory given and lists all files
*	that contain the extension given.
*
* Pre-Conditions:
*	directory - directory to begin search from for extension 
*	ext - string of the extension to look for 
*
*************************************************************************/
void Directory::_iterateAll(node& directory, string ext)
{
	cout << "\n__________________________" << endl;
	cout << "All files with extension "<< ext.c_str() << " in: " << directory.filename.c_str() << ": " << endl;
	cout << "Path: " << directory.path.c_str() << endl << endl;
	cout << "Filename" << setw(76) << "Path" << endl; 
	cout << "---------" << setw(80) << "---------" << endl;

	ForwardIterator<node> traverse(&directory.subdirectories);

	for (traverse.Reset(); !traverse.IsDone(); traverse.MoveNext())
	{
		string name = traverse.GetCurrent()->filename;
		if (name.find(ext) != string::npos)
		{
			cout << "- " << setw(78) << left << name.c_str() << right << traverse.GetCurrent()->path.c_str() << endl;
		}
	}
	cout << "___________________________" << endl;
}

/************************************************************************
* Purpose:
*	this function recursively iterates through the directory and all sub
*	directories to output every file beginning from the directory given.
*	if a subdirectory is found, this function will format the subdirectory
*	by tabbing over x amount of times. 
*
* Pre-Conditions:
*	directory - directory to begin from 
*	subdir - boolean flag to indicate a subdirectory. 
*
*************************************************************************/
void Directory::_iterateRecursive(node& directory, bool& subdir)
{
	if (directory.subdirectories.getHead())
	{
		ForwardIterator<node> traverse(&directory.subdirectories);

		for (traverse.Reset(); !traverse.IsDone(); traverse.MoveNext())
		{
			string name = traverse.GetCurrent()->filename;
			if(subdir)
			{
				for (int i = 0; i < Tabs; i++)
					cout << "\t";
			}
			cout << "- " <<name.c_str() << endl;
			if(traverse.GetCurrent()->subdirectories.getHead())
			{
				subdir = true;
				Tabs++; 
				_iterateRecursive(*traverse.GetCurrent(), subdir);
				Tabs--; 
			}
				
		}
	}
}

/************************************************************************
* Purpose:
*	this function recursively searches and lists files in given directory
*	with matching given extension. if a subdirectory is found, this function 
*	will format the subdirectory by tabbing over x amount of times. 
*
* Pre-Conditions:
*	directory - directory to begin from
*	subdir - boolean flag to indicate a subdirectory.
*	ext - string of the extension to look for 
*
*************************************************************************/
void Directory::_iterateRecursive(node& directory, bool& subdir, string ext)
{
	if (directory.subdirectories.getHead())
	{
		ForwardIterator<node> traverse(&directory.subdirectories);

		for (traverse.Reset(); !traverse.IsDone(); traverse.MoveNext())
		{
			string name = traverse.GetCurrent()->filename;

			if (name.find(ext) != string::npos)
			{
				cout << "- " << setw(78) << left << name.c_str() << right <<  traverse.GetCurrent()->path.c_str() << endl;
			}

			if (traverse.GetCurrent()->subdirectories.getHead())
			{
				subdir = true;
				Tabs++;
				_iterateRecursive(*traverse.GetCurrent(), subdir, ext);
				subdir = false; 
				Tabs--;
			}

		}
	}
}
