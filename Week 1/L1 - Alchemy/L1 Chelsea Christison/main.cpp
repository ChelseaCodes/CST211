/*************************************************************
* Author:			Chelsea Christison
* Date Created: 4.12.2017
* 
* Lab/Assignment: Lab 1 – Alchemy Game
*
* Overview:
*	This program simulates the game of Alchemy. User can
*	use WASD to manouver around the board, and can place
*	a tile using the 'e' key. User can only place a tile
*	next to a wild tile, or a tile of like symbol or color.
*	user can also use a bomb, X, and erase a single tile.
*
* Input:
*	The input consists of keyboard inputs: q, w, a, s, d,
*	e, r and n. 
*
* Output:
*	The output is the UI of Alchemy. Includes the score, 
*	number of strikes against discarding, how to play, the 
*	board itself, and a legend of keys. 
*
*
* NOTE: due to time restraints, this is not fully documented. 
************************************************************/
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <ctime>
using std::cout;
using std::endl; 
#include"control.h"
#include "rlutil.h"
#include <windows.h>

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));

	Control Alchemy; 
	Alchemy.play();	//display the board once

	return 0; 
}