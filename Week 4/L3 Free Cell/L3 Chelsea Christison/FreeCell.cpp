/*************************************************************
* Author:		Chelsea Christison
* Filename:		playcards.cpp
* Date Created:	5.2.2017
* Modifications:
**************************************************************/
#include "FreeCell.h"

FreeCell::FreeCell(): m_error_flag(false)
{
	for(int i = 0; i < MAX_COL; i++)
	{
		if(i < MAX)
		{
			m_f_inputs[i] = m_h_inputs[i] = i; 
		}
		m_p_inputs[i] = i; 
	}
}

FreeCell::~FreeCell()
{}

/*************************************************************
* Purpose:
*	This function is to drive the game from main.
**************************************************************/
void FreeCell::Play()
{
	Display(); 
	UserInput(); 
}

/*************************************************************
* Purpose:
*	This function is used to drive the display onto console.
*	It calls the display functions of the three main components
*	of the game: Playarea, Freecells, and Homecells. 
**************************************************************/
void FreeCell::Display()
{
	system("cls"); 
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD C;
	C.X = TITLE_X;
	C.Y = TITLE_Y; 

	DisplayHowToPlay();
	if (m_error_flag)
		DisplayError(m_saved_error); 

	SetConsoleCursorPosition(output, C); 
	//light blue text for background
	SetConsoleTextAttribute(output, 259);
	cout << "FreeCell"; 
	SetConsoleTextAttribute(output, 15);

	m_play_area.DisplayPlayArea(); 
	m_free_cells.DisplayFreeCells(); 
	m_home_cells.DisplayHomeCells(); 

	SetConsoleTextAttribute(output, 15);
}

/*************************************************************
* Purpose:
*	This function displays how to play FreeCell in their 
*	console window complete with commands. 
*	User has the option of a cheat button.
**************************************************************/
void FreeCell::DisplayHowToPlay()
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD H; 
	H.X = HOWTO_X;
	H.Y = HOWTO_Y; 

	//pink text
	SetConsoleTextAttribute(output, 269);

	SetConsoleCursorPosition(output, H); 
	cout << " = How To Play FreeCell =  ";
	H.Y++; 
	SetConsoleCursorPosition(output, H);
	cout << " Move inputs: ";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "    'P' - play area";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "    'F' - freecell area";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "    'H' - homecell area";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "    'Q' - Quit game, 'X' - quick cheat";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << " Allowable moves:  (some moves don't require an index)";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << " P -> {P, H, F}; F -> {P, H} "; 
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "Example: 'P0H' moves card from play area 0, to its homecell"; 
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "Example: 'P0f' moves card from play area 0, to next available freecell";
	H.Y++;
	SetConsoleCursorPosition(output, H);
	cout << "Example: 'F1P0' moves card in freecell[1] to playarea[0] ";

	SetConsoleTextAttribute(output, 15);
}

/*************************************************************
* Purpose:
*	This function is used to display errors onto the console.
*	since a console clear screen is used, this function sets
*	a flag, and saves the error passed for reprint upon
*	re-display. This way user can see the error. 
**************************************************************/
void FreeCell::DisplayError(string error)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD E;
	E.X = ERROR_X; 
	E.Y = ERROR_Y; 

	//pink text
	SetConsoleTextAttribute(output, 268);

	SetConsoleCursorPosition(output, E);
	cout << "!!Error!!  ";
	E.Y++; 
	SetConsoleCursorPosition(output, E);
	cout << error;

	SetConsoleTextAttribute(output, 15);

	if (m_error_flag)
	{
		m_error_flag = false;
		m_saved_error = ""; 
	}
	else
	{
		m_error_flag = true; 
		m_saved_error = error; 
	}
}

/*************************************************************
* Purpose:
*	This function drives the loop of the game until user
*	quits or wins. User has the option of a "cheat" mode, 
*	which will run predefined commands on an unshuffled deck
*	to arrive at 2 moves left to win. 
**************************************************************/
void FreeCell::UserInput()
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD U;
	char first_move = '/0';
	char second_move = '/0';
	//indicies
	int x = 0;	
	int y = 0; 
	//autoplay 
	bool auto_play = false; 
	bool auto_play2 = false; 
	int auto_play_i = 0; 

	do
	{
		char input[5]{ '/0' }; // input[4] is '/0'

		Display();

		//set space for user input 
		U.X = USERINPUT_X;
		U.Y = USERINPUT_Y;
		SetConsoleCursorPosition(output, U);
		cout << "				"; 
		//light blue text for background
		SetConsoleTextAttribute(output, 259);
		U.X;
		SetConsoleCursorPosition(output, U);
		cout << "Move: ";

		//if auto play is enabled
		if(auto_play)
		{
			if (auto_play_i < MOVES)
			{
				strcpy(input, m_auto_play_1[auto_play_i]);
				cout << input;
				auto_play_i++;
			}
			else
				auto_play = false;
			
		}
		else if(auto_play2)
		{
			if (auto_play_i < auto2)
			{
				strcpy(input, m_auto_play_1[auto_play_i]);
				cout << input;
				auto_play_i++;
			}
			else
				auto_play2 = false;
			
		}
		else
		{
			//get input from user
			std::cin.ignore(std::cin.rdbuf()->in_avail());
			std::cin.getline(input, 5);
			std::cin.clear();
		}

		// 0[P,F] 1[#] 2[P,F,H] 3[#]
		first_move = toupper(input[0]); 
		second_move = toupper(input[2]);
		input[1] == 0 ? x = 0 : x = input[1] - '0';
		input[3] == 0 ? y = 0 : y = input[3] - '0'; 

		/* Two types of 1st moves: Playarea and FreeCell */
		switch(first_move)
		{
			/*  FROM playarea  */
			case 'P':
				if (m_check_range(x,'P'))	//check range of number given
				{
					if (m_play_area.m_play_cards[x].isEmpty())
						DisplayError("No cards to move in this stack");
					else
					{
						/* 3 move types from playarea: freecell, playarea, homecells */
						switch (second_move)
						{
							/*  FROM playarea[x] TO freecells  */
							case'F':
								if (!m_free_cells.isFull())
									m_Play_to_Free(x);
								else
									DisplayError("No open FreeCells");
								break;
							/*  FROM playarea[x] TO playarea[y]  */
							case'P':
								if (m_check_range(y, 'P') && x != y)	//x!=y - can't move onto itself. 
									m_Play_to_Play(x, y);
								else
									DisplayError("Column number is out of bounds");
								break;
							/*  FROM playarea[x] TO homecells  */
							case'H':
								m_Play_to_Home(x);
								break;
							default:;
						}//end second_move switch
					}
				}
				else
					DisplayError("Column given is out of range");
			break;
			/*  FROM freecells  */
			case 'F':
				if(!m_free_cells.isEmpty())
				{
					if (!m_check_range(x, 'F'))
						DisplayError("Freecell column given is out of range");
					else
					{
						/* 2 types of moves from freecells: playarea, homecells */
						switch (second_move)
						{
							/*  FROM freecells[x] TO playarea[y]  */
							case'P':
								if (m_check_range(y, 'P'))
									m_Free_to_Play(x, y);
								else
									DisplayError("Playarea column number is out of bounds");
								break;
							/*  FROM freecells[x] TO homecells  */
							case'H':
								m_Free_to_Home(x);
								break;
						default:;
						}//end second_move switch
					}
				}
				else
					DisplayError("Error: no card in freecell");
				break;
			case 'Q':
				break;
			case 'X':
				auto_play = true; 
				m_play_area.m_cheat_mode(); 
				break;
			case 'Y':
				auto_play2 = true; 
				m_play_area.m_cheat_mode(); 
				break; 
			default:
				DisplayError("input error"); 
		}
		Display();
	} while (first_move != 'Q' && !m_check_win());	//exit program

	SetConsoleTextAttribute(output, 15);
}

/*************************************************************
* Purpose:
*	This function checks the range of the index provided by 
*	the user for a given type of move. 
**************************************************************/
bool FreeCell::m_check_range(int n, char type)
{
	bool in_range = false; 

	switch(type)
	{
	case 'P':
		if (n < MAX_COL && n > -1)
			in_range = true; 
		break;
	case 'F':
		if (n < MAX && n > -1)
			in_range = true;
		break;
	default:;
	}

	return in_range; 
}

/*************************************************************
* Purpose:
*	This function checks card A and card B to see if they are
*	able to be stacked. returns a bool
**************************************************************/
bool FreeCell::m_check_card_placement(Card before, Card after)
{
	bool okay_to_place = false; 
	Card::Rank A_R = after.GetRank(); 
	Card::Suit A_S = after.GetSuit(); 
	Card::Rank B_R = before.GetRank();
	B_R--;  //decrement one less
	Card::Suit B_S = before.GetSuit(); 

	// card after is Spades or Clubs 
	// AND card before is a Hearts or Diamonds
	// AND card after's rank is one less than card before's
	if ((A_S == Card::SPADES || A_S == Card::CLUBS)
		&& (B_S == Card::HEARTS || B_S == Card::DIAMONDS)
		&& (A_R == B_R))
		okay_to_place = true;
	else if ((A_S == Card::HEARTS || A_S == Card::DIAMONDS)
		&& (B_S == Card::SPADES || B_S == Card::CLUBS)
		&& A_R == B_R)
		okay_to_place = true; 


	return okay_to_place; 
}

/*************************************************************
* Purpose:
*	This function sets a freecell to a card off the playarea
*	at an index
**************************************************************/
void FreeCell::m_Play_to_Free(int play_index)
{
	//take card at the play index and send to an open freecell
	m_free_cells.setCell(m_play_area.m_play_cards[play_index].Pop());
}

/*************************************************************
* Purpose:
*	This function places a playarea card at an index into
*	the homecells, if it is able
**************************************************************/
void FreeCell::m_Play_to_Home(int play_index)
{
	Card c = m_play_area.m_play_cards[play_index].Peek(); 

	if (m_home_cells.setHomeCell(c))
		m_play_area.m_play_cards[play_index].Pop();
	else
		DisplayError("Incorrect card to place into home");
}

/*************************************************************
* Purpose:
*	This function places a card or stack of cards, into
*	another section of the playarea. 
**************************************************************/
void FreeCell::m_Play_to_Play(int play_index_1, int play_index_2)
{
	int row = 0; 
	int allowable_transfers = m_free_cells.m_open_cells + m_play_area.m_number_of_open_stacks() + 1; 
	int intended_transfers = 0; 
	bool check_more_cards = false;
	bool empty_stack = false; 
	LStack<Card> transfer_cards;
	Card a, b;
	Card topcardstack1, topcardstack2;
	
	//moving from stack to empty stack
	if(m_play_area.m_play_cards[play_index_2].isEmpty())
	{
		check_more_cards = empty_stack = true; 
	}
	else
	{
		//first check if one card is moveable
		topcardstack1 = m_play_area.m_play_cards[play_index_1].Peek();
		topcardstack2 = m_play_area.m_play_cards[play_index_2].Peek(); 	

		// if able to place at least one card, num of movable cards is 1, if not - Check for more cards. 
		m_check_card_placement(topcardstack2, topcardstack1) ? check_more_cards = false : check_more_cards = true;
	}
	

	if (check_more_cards)
	{
		if(m_auto_play_1)
		{
			if(row_input_i < ROW_INPUTS)
				row = m_auto_row_input[row_input_i++]; 
		}
		else
			row = m_get_row_to_start(); // what row does the user want to begin moving from 
	
		//calculate if intended transfers is allowable
		int size_of_stack = m_play_area.m_play_cards[play_index_1].Size(); 
		intended_transfers = (size_of_stack - row);	//size - row gives # of comparisons. + 1 gives total cards
		/*if (intended_transfers > 2)
			intended_transfers++; */

		if (intended_transfers <= allowable_transfers)
		{
			//pop first, peek second - first pass
			a = m_play_area.m_play_cards[play_index_1].Pop();
			b = m_play_area.m_play_cards[play_index_1].Peek();

			//loop from 1 to size of original stack - rows -> number of passes to check placement
			for (int i = 0; i < intended_transfers - 1 && check_more_cards; i++)
			{
				//if cards are placeable 
				if (m_check_card_placement(b, a))
				{
					transfer_cards.Push(a);	//push onto transfer and get next cards in stack
					a = m_play_area.m_play_cards[play_index_1].Pop();
					b = m_play_area.m_play_cards[play_index_1].Peek();
				}
				//stop checking if stack isn't valid
				else
					check_more_cards = false;
			}

			//if stack was valid and second stack isnt empty
			if (check_more_cards)
			{
				if (!empty_stack)
				{
					//peek at the card to place on top of
					b = m_play_area.m_play_cards[play_index_2].Peek();

					//ensure beginning of stack (a) is placeable onto b
					if (m_check_card_placement(b, a))
					{
						m_play_area.m_play_cards[play_index_2].Push(a);		//set topmost card first
																			//push the rest of the cards 
						//for (int i = 0; i < transfer_cards.; i++)
							while(!transfer_cards.isEmpty())
								m_play_area.m_play_cards[play_index_2].Push(transfer_cards.Pop());
					}
					else
					{
						//push a back onto original spot
						m_play_area.m_play_cards[play_index_1].Push(a);
						while (!transfer_cards.isEmpty())
							m_play_area.m_play_cards[play_index_1].Push(transfer_cards.Pop());

						DisplayError("Invalid move");
					}
				}
				else //nocheck
				{
					m_play_area.m_play_cards[play_index_2].Push(a);		//set topmost card first
																		//push the rest of the cards 
					//for (int i = 0; i < transfer_cards.Size(); i++)
					while (!transfer_cards.isEmpty())
						m_play_area.m_play_cards[play_index_2].Push(transfer_cards.Pop());
				}
			}
			//invalid stack - re - build original stack. 
			else
			{
				//push a back onto original spot
				m_play_area.m_play_cards[play_index_1].Push(a);
				while (!transfer_cards.isEmpty())
					m_play_area.m_play_cards[play_index_1].Push(transfer_cards.Pop());

				DisplayError("Invalid move");
			}
		}
		//if intended moves exceeded allowed
		else
			DisplayError("Can't move that many cards"); 		
	}
	//if moving one card 
	else
	{
		m_play_area.m_play_cards[play_index_2].Push(topcardstack1); 
		m_play_area.m_play_cards[play_index_1].Pop(); 
	}
}

/*************************************************************
* Purpose:
*	This function places a card from freecells at an index
*	into a homecell, if able. 
**************************************************************/
void FreeCell::m_Free_to_Home(int free_index)
{
	Card a = m_free_cells.peekCellCard(free_index); 

	if (m_home_cells.setHomeCell(a))
		m_free_cells.getCellCard(free_index);
	else
		DisplayError("Incorrect card to place in home "); 
}

/*************************************************************
* Purpose:
*	This function places a card from freecells at an index
*	into the playarea at an index, if able.
**************************************************************/
void FreeCell::m_Free_to_Play(int free_index, int play_index)
{
	Card a = m_free_cells.peekCellCard(free_index);	//card to place back to playfield
	if (m_play_area.m_play_cards[play_index].isEmpty())
	{
		m_play_area.m_play_cards[play_index].Push(a);
		m_free_cells.getCellCard(free_index);	//remove card from free cells
	}
	else
	{
		Card b = m_play_area.m_play_cards[play_index].Peek();	//card to look at	

		// Check card placement 
		if (m_check_card_placement(b, a))
		{
			m_play_area.m_play_cards[play_index].Push(a);	//push
			m_free_cells.getCellCard(free_index);	//remove card from free cells
		}
	}
	
}

/*************************************************************
* Purpose:
*	This function is called when a user can possibly move 
*	more than one card as a stack, onto a different part 
*	of the play area. prompts user to specify the top
*	card of a stack they would like to move, by asking for
*	the row the card is in, in the specified column. 
**************************************************************/
int FreeCell::m_get_row_to_start()
{
	//display number of cards 
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD U;
	int input; 
	bool wrong_input = true; 

	do
	{
		//set space for user input 
		U.X = USERINPUT_X;
		U.Y = USERINPUT_Y + 1;
		SetConsoleCursorPosition(output, U);
		cout << "				";
		//light blue text for background
		SetConsoleTextAttribute(output, 259);
		U.X;
		SetConsoleCursorPosition(output, U);
		cout << "Indicate which row to move card stack from: ";
		//get input from user
		std::cin >> input; 
		
		//if input is in range: -1 < input <= largest 
		if (input < m_play_area.m_largest_stack_size && input > -1)
			wrong_input = false;
		else
			DisplayError("Row specified is out of range"); 

	} while (wrong_input);

	//reset 
	SetConsoleCursorPosition(output, U);
	cout << "																	";

	return input; 
	SetConsoleTextAttribute(output, 15);
}

/*************************************************************
* Purpose:
*	This function checks if the homecells are full, indicating
*	a win. 
**************************************************************/
bool FreeCell::m_check_win()
{
	bool win = true; 
	for(int i = 0; i < MAX; i++)
	{
		if (!m_home_cells.m_home_cells[i].isFull())
			win = false; 
	}

	if(win)
	{
		cout << "YOU'VE WON\n\n\n\n\n\n\n\n\n"; 
	}

	return win; 
}

