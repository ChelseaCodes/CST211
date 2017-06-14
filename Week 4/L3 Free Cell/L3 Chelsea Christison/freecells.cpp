/*************************************************************
* Author:		Chelsea Christison
* Filename:		freecells.cpp
* Date Created:	4.30.2017
* Modifications:
**************************************************************/
#include "freecells.h"


FreeCells::FreeCells() : m_open_cells(4)
{
	m_free_cells.setLength(MAX_CARDS);  
	for (int i = 0; i < MAX_CARDS; i++)
		m_header_numbers[i] = i; 
}

void FreeCells::setCell(Card card)
{
	if (isFull())
		throw Exception("Free Cells are full"); 

	m_free_cells[MAX_CARDS - m_open_cells] = card;
	m_open_cells--;
}

Card FreeCells::getCellCard(int index)
{
	if (isEmpty())
		throw Exception("Free Cells are empty"); 

	Card c = m_free_cells[index];

	//reset the card. 
	m_free_cells[index].SetRank(Card::FREE); 
	m_free_cells[index].SetSuit(Card::JOKER);
	m_open_cells++; 

	m_shift_down(); 

	return c; 
}

Card FreeCells::peekCellCard(int index)
{
	if (isEmpty())
		throw Exception("Free Cells are empty");

	Card c = m_free_cells[index];

	return c;
}

bool FreeCells::isFull() const
{
	return m_open_cells == 0; 
}

bool FreeCells::isEmpty() const
{
	return m_open_cells == MAX_CARDS; 
}

void FreeCells::DisplayFreeCells() const
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD N;
	N.X = X_COORD; 
	N.Y = Y_COORD - 1; 

	int x = X_COORD;
	int y = Y_COORD;

	for(int i = 0; i < MAX_CARDS; i++)
	{
		SetConsoleCursorPosition(output, N); 
		cout << m_header_numbers[i]; 

		m_free_cells[i].PrintCard(x, y);
		N.X = x += 4; 
	}
}

int FreeCells::numberOfCellsOpen() const
{
	return m_open_cells; 
}

FreeCells::~FreeCells()
{
}

/*************************************************************
* Purpose:
*	This function rewrites the array to keep values without 
*	gaps in between. 
**************************************************************/
void FreeCells::m_shift_down()
{
	Card movecards[MAX_CARDS]; 

	int moveindex = 0; 
	if(!isEmpty())
	{
		for(int i = 0; i < MAX_CARDS; i++)
		{
			if (m_free_cells[i].GetSuit() != Card::JOKER)
				movecards[moveindex++] = m_free_cells[i]; 
		}
		for (int i = 0; i < MAX_CARDS; i++)
			m_free_cells[i] = movecards[i]; 
	}
}
