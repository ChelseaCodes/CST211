/*************************************************************
* Author:			Chelsea Christison
* Date Created:		5.17.2017
*
* Lab/Assignment: Lab 5 - Directory Traversal 
*
* Overview:
*	This program stores all directory and file names into a 
*	data structure called Directory. It also allows the user 
*	to traverse the directory based on a small list of 
*	commands. 
*	
* Input:
*	The input is commands given in from console: 
*	list c:\Test - shows all files in directory only
*	list c:\Test\*.docx - shows all files in dir. with the 
*							same extension 
*	list -r c:\Test\*.docx - shows all files in dir and 
*							sub dirs with same extension. 
*	list code - shows all files that have the keyword 'code'
*				in the filename. 
*
* Output:
*	The output of this program is the results from the commands
*	given from the console. 
*
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <string>
#include <stack>
using std::string;

#include <iostream>
using std::cout; 
using std::endl; 

#include<fstream>
using std::ofstream; 

#include "directory.h"

void menu(Directory* dir);
bool processCommand(string command, Directory& dir); 

int main(int argc, char * argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	ofstream out("dirinfo.txt"); 
	
	cout << "Loading Directory at " << argv[1] << endl;
	Directory dir(argv[1]); 
	cout << "Directory Loaded" << endl; 

	Directory c = dir; 
	menu(&dir); 
		
	return 0;
}

/************************************************************************
* Purpose:
*	this function displays a simple menu for the user to enter a command
*	to search the Directory. Calls a function to process the command 
*	and ensure command is valid. 
*
* Pre-Conditions:
*	dir	- Directory structure 
*
*************************************************************************/
void menu(Directory* dir)
{
	string userin;
	do
	{
		char userinput[300] = { '\0' };
		cout << "command: ('exit' to quit)" << endl;
		std::cin.getline(userinput, 300);

		userin = userinput;
		if (userin != "exit")
			processCommand(userin, *dir);
	} while (userin != "exit"); 
	cout << "Goodbye!" << endl; 
}

/************************************************************************
* Purpose:
*	this function process the command passed by parsing it. Calls 
*	commands on the Directory passed depending on the command 
*	given. 
*
* Pre-Conditions:
*	dir - directory structure to look in 
*	command - string of the command typed by use 
*
*************************************************************************/
bool processCommand(string command, Directory& dir)
{
	bool recursion = false;
	bool pass = true; 

	//finds keyword and removes it - otherwise doesn't pass
	if (command.find("list") != string::npos)
	{
		command = command.erase(0, 5);
	}
	else
	{
		pass = false;
		cout << "\n Invalid command" << endl; 
	}
		

	//if recursion keyword is found, sets flag and erases
	if (command.find("-r") != string::npos && pass)
	{
		recursion = true;
		command = command.erase(0, 3); 
	}

	string directory; 
	string extention; 
	//if a directory is listed 
	if(command.find(':\\') != string::npos && pass)
	{
		// then check for possible *extension 
		if(command.find('*') != string::npos)
		{
			int pos = command.find_first_of('*'); //pass over directory
			extention = command.substr(pos + 1); 
			directory = command.substr(0, pos - 1);	//exclude '*'
			pass = dir.directoryExists(directory); 
			if (pass)
				dir.listDirectory(directory, recursion, extention); 
		}
		else
		{
			directory = command;
			pass = dir.directoryExists(directory); //search entire Dir for directory
			if (pass)
				dir.listDirectory(directory, recursion);
			else
				cout << "\nDirectory does not exist" << endl;
		}
			
	}
	else if (pass)	//what's left should be just a string to search for
	{
		//search and list DS for string "command" 
		dir.listDirectory(command); 
	}

	return pass; 
}
