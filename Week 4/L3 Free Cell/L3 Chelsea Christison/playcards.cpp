/*************************************************************
* Author:		Chelsea Christison
* Filename:		playcards.cpp
* Date Created:	5.1.2017
* Modifications:
**************************************************************/
#include"playcards.h"

PlayCards::PlayCards(): m_largest_stack_size(7)
{
	m_populate_play_area(); 
	for(int i = 0; i < MAX_COL; i++)
	{
		m_empty_stack[i].SetRank(Card::Rank::PLAY);
		m_header_numbers[i] = i;
	}
}

/*************************************************************
* Purpose:
*	This function displays the play area portion of the 
*	FreeCell game
**************************************************************/
void PlayCards::DisplayPlayArea()
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);	
	COORD C, N, S; 

	N.X = C.X = PC_X_COORD;
	C.Y = PC_Y_COORD;
	N.Y = PC_Y_COORD - 1; 

	for (int i = 0; i < MAX_COL; i++)
	{
		if (m_play_cards[i].Size() == 0)
		{
			int x = C.X;
			int y = C.Y; 
			m_empty_stack[i].PrintCard(x, y); 
		}

		m_play_cards[i].DisplayStack(output, C);
		 
		SetConsoleCursorPosition(output, N); 
		cout << m_header_numbers[i]; 
		N.X = C.X += 4; 
	}

	//calculate display for labeling rows
	m_largest_stack_size = m_play_cards[0].Size(); 
	for(int i = 1; i < MAX_COL; i++)
	{
		if (m_largest_stack_size < m_play_cards[i - 1].Size())
			m_largest_stack_size = m_play_cards[i - 1].Size();
	}

	S.X = PC_X_COORD - 2; 
	S.Y = PC_Y_COORD; 

	for(int i = 0; i < m_largest_stack_size; i++)
	{
		SetConsoleCursorPosition(output, S); 
		cout << i; 
		S.Y++; 
	}	
}

PlayCards::~PlayCards()
{
}

/*************************************************************
* Purpose:
*	This function populates the playarea deck. Shuffling 
*	cards before pushing onto the array of linked list stacks
**************************************************************/
void PlayCards::m_populate_play_area()
{
	m_play_deck = Deck();
	m_play_deck.Shuffle(); 
	m_play_deck.Shuffle(); 

	int max_populate = 7; 
	for (int i = 0; i < MAX_COL; i++)
	{
		for(int j = 0; j < max_populate; j++)
		{
			m_play_cards[i].Push(*(m_play_deck.Deal())); 
		}
		if (i == 3)
			max_populate = 6; 
	}
}

/*************************************************************
* Purpose:
*	This function returns the number of open stacks at any 
*	given point. 
**************************************************************/
int PlayCards::m_number_of_open_stacks()
{
	int num = 0; 
	for(int i = 0; i < MAX_COL; i++)
	{
		if (m_play_cards[i].isEmpty())
			num++; 
	}

	return num; 
}

/*************************************************************
* Purpose:
*	This function enables cheat mode by populating the deck
*	without shuffling the cards. 
**************************************************************/
void PlayCards::m_cheat_mode()
{
	Deck new_deck; 
	int max_populate = 7;

	for (int i = 0; i < MAX_COL; i++)
	{
		while (!m_play_cards[i].isEmpty())
			m_play_cards[i].Pop(); 
	}


	for (int i = 0; i < MAX_COL; i++)
	{
		for (int j = 0; j < max_populate; j++)
		{
			m_play_cards[i].Push(*(new_deck.Deal()));
		}
		if (i == 3)
			max_populate = 6;
	}
}

/*************************************************************
* Purpose:
*	This function empties the stack at column 5. 
**************************************************************/
void PlayCards::m_empty_play_stack()
{
	int stack_to_empty = 5; 
	for(int i = 0; i < 6; i++)
	{
		if (i != 5)
			m_play_cards[i].Push(m_play_cards[stack_to_empty].Pop());
		else
			m_play_cards[++i].Push(m_play_cards[stack_to_empty].Pop());
	}
}