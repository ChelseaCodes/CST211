/************************************************************************
* Class: HomeCells
*
* Purpose:
*	This class creates the Free Cells array in the game FreeCell.
*	Implements using the Array Class, and holds addresses to Card Objects
*
* Manager functions:
* 	HomeCells()
*
* Methods:
*
*************************************************************************/
#ifndef HOMECELLS_H
#define HOMECELLS_H
#include "stack.h"
#include "card.h"

const int MAX = 4; 
const int SPADES = 0; 
const int HEARTS = 1; 
const int CLUBS = 2; 
const int DIAMONDS = 3; 

const int HC_X_COORD = 52;
const int HC_Y_COORD = 5;

class HomeCells
{
	friend class FreeCell; 
public:
	HomeCells(); 
	HomeCells(const HomeCells& copy); 
	HomeCells& operator=(const HomeCells& rhs); 
	~HomeCells();

	bool setHomeCell(Card card); 
	void DisplayHomeCells(); 
private:
	Stack<Card> m_home_cells[MAX];
	bool m_pushHomeCell(Card card, int cell_slot); 
	//a var to indicate winning the game (all stacks are full - in order)
};

#endif