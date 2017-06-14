/************************************************************************
* Class: Card
*
* Purpose: 
*	This class creates a Card object. Contains two enums, Rank 
*	and Suit to reflect that of an actual card. Having the enums inside
*	the Card class allows for a Card object to always have a Suit and Rank
*	rather than having a card object with no Suit or Rank, and having 
*	to assign. Suit enums are assigned their respective ASCII values 
*	for easy output to console. 
*	(if using Windows 10, allow console
*	to use Legacy ASCII values to see suit outputs) 
*
* Manager functions:
* 	Card()
* 	Card(Rank rank, Suit suit)
* 		sets the card to the rank and suit passed
* 	~Card()
*
* Methods:
*	void Display()
*		not used. Displays the card in the format "Ace of Spades" for 
*		example
*	void PrintCard(int & X, int & Y)
*		prints card using ASCII art output
*	void PrintTop()			
*		Prints top of card
*	void PrintRank()
*		Prints card rank at top of card
*	void PrintFill()
*		Prints filler for card
*	void PrintSuit()
*		Prints the suit
*	void PrintSecondRank()
*		Prints card rank at bottom of card
*	void PrintBottom()
*		Prints bottom of card
*	
*************************************************************************/
#ifndef CARD_H
#define CARD_H
#include <windows.h>
#include<iostream>
using std::cout;
using std::endl;

#include<iomanip>
using std::setw; 
using std::setfill; 
using std::right;
using std::left; 

#include<ostream>
using std::ostream; 

class Card
{
	public:
		enum Rank{ ACE = 1, DEUCE, TREY, FOUR, 
				   FIVE, SIX, SEVEN, EIGHT,
				   NINE, TEN, JACK, QUEEN, KING, FREE = 'F', HOME = 'H', PLAY = 'P'};

		//suits reflect their ascii equivalents 
		enum Suit{ SPADES = 6, HEARTS = 3, CLUBS = 5, DIAMONDS = 4, JOKER = 'C' };

		Card();
		Card(const Card& copy);
		Card& operator=(const Card& rhs); 
		Card(Rank rank, Suit suit); 
		void SetRank(Rank r);
		void SetSuit(Suit s);
		Rank GetRank() const;
		Suit GetSuit() const;

		void Display() const;
		void PrintCard(int & X, int & Y);
		friend ostream& operator<<(ostream & os, const Card& rhs); 
		~Card();
		bool operator==(const Card& rhs) const; 
	private:
		Rank m_rank; 
		Suit m_suit; 

		void SetCursor(HANDLE hStdout, COORD cursor, int X, int Y);	//set the cursor 
		void PrintRank();		//Prints card rank at top of card
		void PrintSuit();			//Prints the suit

};
Card::Suit operator++(Card::Suit& rs, int);
Card::Rank operator++(Card::Rank& rs, int);
Card::Rank operator--(Card::Rank& rs, int); 
#endif 