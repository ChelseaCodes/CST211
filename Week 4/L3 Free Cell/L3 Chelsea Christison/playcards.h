/************************************************************************
* Class: PlayCards
*
* Purpose:
*	This class creates the playing field for FreeCell using a linked list
*	based stack array. 
*
* Manager functions:
* 	PlayCards()
*	~PlayCards()
* Methods:
*	DisplayPlayArea()
*		displays the cards in the playarea
*	m_empty_play_stack()
*		empties a stack in the playarea
*	m_populate_play_area()
*		populates the stacks with cards
*	m_number_of_open_stacks()
*		returns the number of open stacks
*	m_cheat_mode() 
*		enables cheat mode, repopulates deck with unshuffled cards
*************************************************************************/
#ifndef PLAYCARDS_H
#define PLAYCARDS_H
#include "lstack.h"
#include "deck.h"

const int MAX_COL = 8; 
const int PC_X_COORD = 25;
const int PC_Y_COORD = 8;

class PlayCards
{
	friend class FreeCell; 
public:
	PlayCards(); 
	~PlayCards(); 
private:
	void DisplayPlayArea(); 
	void m_empty_play_stack(); 
	LStack<Card> m_play_cards[MAX_COL];
	Deck m_play_deck; 
	Card m_empty_stack[MAX_COL]; 
	void m_populate_play_area(); 
	int m_header_numbers[MAX_COL];
	int m_largest_stack_size; 
	int m_number_of_open_stacks(); 
	void m_cheat_mode(); 

};
#endif