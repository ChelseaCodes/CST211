/************************************************************************
* Class: Deck
*
* Purpose: 
*	This class creates a Deck object that holds an array of 52
*	cards, and an integer to keep track of where in the array a user is. 
*
* Manager functions:
* 	Deck()
*	~Deck()
*	
* Methods:
*	void Shuffle()
*		using the Fisher and Yates shuffling algorithm, shuffles cards 
*	Card Deal()
*		returns a single card to the caller, and moves to the next 
*		card in the array for when this function is called again. 
*		Checks if object is at the end of the array, and reshuffles in 
*		the case that it is. 
*		
*************************************************************************/
#ifndef DECK_H
#define DECK_H

#include "card.h"
#include "array.h"

const int DECK_OF_CARDS = 52;
class Deck
{
	public:
		Deck();

		void Shuffle();
		Card* Deal(); 

		~Deck();
	private:
		Array<Card> m_deck;	
		int m_currentcard;
};
#endif

