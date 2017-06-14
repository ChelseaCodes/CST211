/*************************************************************
* Author:			Chelsea Christison
* Date Created:		4.30.2017
*
* Lab/Assignment: Lab 3 - Free Cell
*
* Overview:
*	This program simulates the game FreeCell in console. 
*	User can input a variety of commands to move the selected
*	cards in the playarea with the overall goal being to 
*	fill the homecells in ascending order by the same Suit. 
*	
* Input:
*	List of inputs from the keyboard are:
*	'Q' - quit game
*	'X'	- enable cheat move, 2 moves left to finish game
*	'P#' - Selects playarea, followed by an index
*	'H' - homecell. Auto places, no index req.
*	'F#' - when sending a card to freecell, an index is NOT
*		  needed. When retreiving a card from a freecell, 
*		  an index will need to be provided
*
* Output:
*	Display to console after processing command. 
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
using std::cout;
using std::cin; 
using std::endl; 
#include <ctime>     // for time

#include "FreeCell.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	srand(time(0));  // initialize seed "randomly"
	FreeCell freecell; 
	freecell.Play();
	cout << "\n\n" <<  endl; 
	return 0; 
}