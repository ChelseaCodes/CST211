/*************************************************************
* Author:		Chelsea Christison
* Filename:		homecells.cpp
* Date Created:	4.30.2017
* Modifications:
**************************************************************/
#include "homecells.h"
#include "freecells.h"

HomeCells::HomeCells()
{
	//set each stack to 13, default card is HOME
	for (int i = 0; i < MAX; i++)
	{
		m_home_cells[i] = Stack<Card>(13);
		m_home_cells[i].Peek().SetRank(Card::Rank::HOME); 
	}
}

HomeCells::HomeCells(const HomeCells& copy) 
{
	for(int i = 0; i < MAX; i++)
	{
		m_home_cells[i] = copy.m_home_cells[i]; 
	}

}

HomeCells& HomeCells::operator=(const HomeCells& rhs)
{
	if(this != & rhs)
	{
		for (int i = 0; i < MAX; i++)
		{
			m_home_cells[i] = rhs.m_home_cells[i];
		}
	}
	return *this; 
}

bool HomeCells::setHomeCell(Card card)
{
	bool pushed = false; 
	switch(card.GetSuit())
	{
	case Card::SPADES:
		pushed = m_pushHomeCell(card, SPADES); 
		break; 
	case Card::HEARTS:
		pushed = m_pushHomeCell(card, HEARTS);
		break;
	case Card::CLUBS:
		pushed = m_pushHomeCell(card, CLUBS);
		break;
	case Card::DIAMONDS:
		pushed = m_pushHomeCell(card, DIAMONDS);
		break;
	case Card::JOKER:
		break;
	default:
		;
	}
	return pushed; 
}

void HomeCells::DisplayHomeCells()
{
	int x = HC_X_COORD;
	int y = HC_Y_COORD;
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int i = 0; i < MAX; i++)
	{
		m_home_cells[i].Peek().PrintCard(x, y); 
		x += 4;
	}
}

HomeCells::~HomeCells()
{
}

bool HomeCells::m_pushHomeCell(Card card, int cell_slot)
{
	Card::Rank R;
	bool pushed = false; 

	//first see what's on the top of the stack; 	
	if(m_home_cells[cell_slot].Size() == 0)
		R = Card::Rank::HOME;
	else
	{
		Card temp = m_home_cells[cell_slot].Peek();
		R = temp.GetRank();
	}

	//is the top of the stack a free cell? 
	//if so, don't increment. otherwise increment
	R == Card::Rank::HOME ? R = R : R++; 
	
	if(R == Card::Rank::HOME && card.GetRank() == Card::Rank::ACE ||
		R == card.GetRank())
	{
		m_home_cells[cell_slot].Push(card); 
		pushed = true; 
	}

	return pushed; 
}

