/*************************************************************
* Author:		Chelsea Christison
* Filename:		deck.cpp
* Date Created:	2.23.2017
* Modifications:	
*	3.6 - fixed enum for loop problem with 
*	overloading the binary ++ operators. And implemented 
*	shuffle algorithm. Changed cards to be an array instead of
*	a pointer to an array. 
*	3.8 - Moved seeding of random to the c'tor 
*	
**************************************************************/
#include "deck.h"

/**********************************************************************
* Purpose: This default Deck constructor utilizes the overloaded ++
*	implemented in the Card class. To populate the deck, this c'tor
*	uses a nested for loop, looping through suit and then rank
*	to populate the deck in order. Deck shuffled after population. 
*
************************************************************************/
Deck::Deck()
{
	m_deck.setLength(DECK_OF_CARDS); 

	int i(0);

	for (Card::Suit suit = Card::HEARTS; suit <= Card::SPADES; suit++)
	{
		for (Card::Rank rank = Card::ACE; rank <= Card::KING; rank++)
		{
			m_deck[i++] = Card(rank, suit);
		}
	}

	//randomize better by shuffling twice
	//Shuffle();
	//Shuffle(); 

	m_currentcard = 0;
}

void Deck::Shuffle()
{
	//shuffles the deck using Fisher & Yates algorithm
	for (int i(0); i < (DECK_OF_CARDS - 2); i++)
	{
		int j = rand() % 52;
		Card temp = m_deck[i];
		m_deck[i] = m_deck[j];
		m_deck[j] = temp;
	}

	m_currentcard = 0;
}

Card* Deck::Deal()
{ 
	if(m_currentcard == DECK_OF_CARDS)
	{
		cout << "\n\nEnd of the Deck\nReshuffling\n" << endl; 
		Shuffle(); 
	}
	return &m_deck[m_currentcard++];
}

Deck::~Deck()
{
}

