/************************************************************************
* Class: FreeCells
*
* Purpose:
*	This class creates the Free Cells array in the game FreeCell.
*	Implements using the Array Class, and holds addresses to Card Objects
*************************************************************************/
#ifndef FREECELLS_H
#define FREECELLS_H
#include "array.h"
#include "card.h"

const int MAX_CARDS = 4; 
const int X_COORD = 13;
const int Y_COORD = 5; 

class FreeCells
{
	friend class FreeCell; 
public:
	FreeCells(); 
	void setCell(Card card); 
	Card getCellCard(int index); 
	Card peekCellCard(int index); 
	bool isFull() const; 
	bool isEmpty() const;
	void DisplayFreeCells() const; 
	int numberOfCellsOpen() const; 
	~FreeCells(); 
private:
	Array<Card> m_free_cells; 
	int m_open_cells; 
	int m_header_numbers[MAX_CARDS];
	void m_shift_down(); 
};
#endif