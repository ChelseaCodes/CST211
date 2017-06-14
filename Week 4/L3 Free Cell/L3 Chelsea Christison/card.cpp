/*************************************************************
* Author:		Chelsea Christison
* Filename:		card.cpp
* Date Created:	2/23/2017
* Modifications: 
*	3.3 - overloaded binary operators. not working
*	3.6 - fixed binary ++ operator overloads. Signature needed
*		  to be added to .h, outside of class definition
*	3.8 - card class now displays itself using ASCII, rather 
*		  than main doing the display. 
*		  
**************************************************************/
#include "card.h"

Card::Card(): m_rank(FREE), m_suit(JOKER)
{}

Card::Card(const Card& copy): m_rank(copy.m_rank), m_suit(copy.m_suit)
{
}

Card& Card::operator=(const Card& rhs)
{
	if(this != & rhs)
	{
		m_rank = rhs.m_rank; 
		m_suit = rhs.m_suit; 
	}
	return *this; 
}

Card::Card(Rank rank, Suit suit): m_rank(rank), m_suit(suit)
{}

void Card::Display() const
{
	const char * ranktext[] = { "Ace", "Deuce", "Trey", "Four", "Five",
		"Six", "Seven", "Eight", "Nine", "Ten",
		"Jack", "Queen", "King" };
	const char * suittext[] = { "Spades","Hearts","Clubs","Diamonds" };

	cout << ranktext[m_rank - 1] << " OF " << suittext[m_suit] << endl; 
}

/**********************************************************************
* Purpose: This function handles the printing and formatting of cards
*	to the console. Will print red text on black background for cards
*	with suit Spades or Clubs, and prints black text on red background
*	for cards with suit Hearts or Diamonds. Also prints the ASCII suit
*
* Stipulations:
*	  No stipulations.
*
* Precondition:
*     X	-	 x coordinate position for printing ASCII card art to console
*     Y	-	 y coordinate position for printing ASCII card art to console
*
* Postcondition:
*      changes the X and Y coordinates for placing the console print
*      cursor where the next card should be printed.
*
************************************************************************/
void Card::PrintCard(int& X, int& Y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;

	//begin at X, Y
	cursor.X = X;
	cursor.Y = Y;
	SetConsoleCursorPosition(output, cursor);

	//Hearts and Diamonds will be printed yellow text on black 
	if (m_suit == Card::HEARTS || m_suit == Card::DIAMONDS)
		SetConsoleTextAttribute(output, 270);
	//Default free cells are bright green on black 
	else if(m_suit == Card::JOKER)
		SetConsoleTextAttribute(output, 266);
	//Spades and Clubs will be bright blue on black 
	else
		SetConsoleTextAttribute(output, 267);

	PrintRank();

	//reset output 
	SetConsoleTextAttribute(output, 15);
}

void Card::SetRank(Rank r)
{
	m_rank = r; 
}

void Card::SetSuit(Suit s)
{
	m_suit = s;
}

Card::Rank Card::GetRank() const
{
	return m_rank;
}

Card::Suit Card::GetSuit() const
{
	return m_suit;
}

Card::~Card()
{
}

bool Card::operator==(const Card& rhs) const
{
	return m_rank == rhs.m_rank && m_suit == rhs.m_suit; 
}

/**********************************************************************
* Purpose: This function sets the cursor for console using the X and Y
*	values passed.
*
* Stipulations:
*	  Caller must specify X and Y values on where to set the position
*
* Precondition:
*     X	 - x coord. on console
*     Y	 - y coord. on console
*
* Postcondition:
*     sets cursor to position passed
*
************************************************************************/
void Card::SetCursor(HANDLE hStdout, COORD cursor, int X, int Y)
{
	cursor.X = X;
	cursor.Y = Y;
	SetConsoleCursorPosition(hStdout, cursor);
}

/**********************************************************************
* Purpose: This function prints the rank at the top of the ASCII card,
*	and prints a J, Q or K instead of 11, 12 or 13.
*
* Stipulations:
*	  No stipulations.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      output to console
*
************************************************************************/
void Card::PrintRank()
{
	char letter = '\0';
	if (m_rank > 10)
	{
		switch (m_rank)
		{
			case JACK:
				letter = 'J';
				break;
			case QUEEN:
				letter = 'Q';
				break;
			case KING:
				letter = 'K';
				break;
			case FREE:
				letter = 'F';
				break; 
			case HOME:
				letter = 'H'; 
				break;
			case PLAY:
				letter = 'P';
				break; 
			default:;
		}

		cout << left << letter << static_cast<char>(m_suit);
	}
	else
	{
		cout << left << m_rank << static_cast<char>(m_suit);
		if (m_rank == 10)
			cout << " "; 
	}

	//resets the console output 
	cout << right;
	//PrintSuit(); 
}

/**********************************************************************
* Purpose: This function prints the suit int the middle of the
*	ASCII card, using the ASCII characters
*
* Stipulations:
*	  If user is on Windows 10, must configure console settings to use
*	  Legacy characters to see the suits.
*
* Precondition:
*     no preconditions
*
* Postcondition:
*      output to console
*
************************************************************************/
void Card::PrintSuit()
{
	cout << static_cast<char>(m_suit) << " ";
}

/**********************************************************************
* Purpose: This function overloads the binary "++" Suit enumerator 
*
* Stipulations:
*	  No stipulations.
*
* Precondition:
*     rs - suit to be post incremented 
*
* Postcondition:
*      increments rs, but returns the old value first(post increment)
*
************************************************************************/
Card::Suit operator++(Card::Suit& rs, int)
{
	Card::Suit old = rs;
	rs = Card::Suit(rs + 1);
	return old;
}

/**********************************************************************
* Purpose: This function overloads the binary "++" Rank enumerator
*
* Stipulations:
*	  No stipulations.
*
* Precondition:
*     rs - rank to be post incremented 
*
* Postcondition:
*      increments rs, but returns the old value first(post increment)
*
************************************************************************/
Card::Rank operator++(Card::Rank& rs, int)
{
	Card::Rank old = rs;
	rs = Card::Rank(rs + 1);
	return old;
}

Card::Rank operator--(Card::Rank& rs, int)
{
	Card::Rank old = rs;
	rs = Card::Rank(rs - 1);
	return old;
}

ostream& operator<<(ostream& os, const Card& rhs)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

	//Hearts and Diamonds will be printed yellow text on black 
	if (rhs.GetSuit() == Card::HEARTS || rhs.GetSuit() == Card::DIAMONDS)
		SetConsoleTextAttribute(output, 270);
	//Default free cells are bright green on black 
	else if (rhs.GetSuit() == Card::JOKER)
		SetConsoleTextAttribute(output, 266);
	//Spades and Clubs will be bright blue on black 
	else
		SetConsoleTextAttribute(output, 267);

	char letter = '\0';
	if (rhs.GetRank() > 10)
	{
		switch (rhs.GetRank())
		{
		case Card::JACK:
			letter = 'J';
			break;
		case Card::QUEEN:
			letter = 'Q';
			break;
		case Card::KING:
			letter = 'K';
			break;
		case Card::FREE:
			letter = 'F';
			break;
		case Card::HOME:
			letter = 'H';
			break;
		case Card::PLAY:
			letter = 'P';
			break;
		default:;
		}

		os << left << letter << static_cast<char>(rhs.GetSuit());
	}
	else
	{
		os << left << rhs.GetRank() << static_cast<char>(rhs.GetSuit());
		if (rhs.GetRank() == 10)
			os << " ";
	}
	//reset output 
	SetConsoleTextAttribute(output, 15);

	return os; 
}
