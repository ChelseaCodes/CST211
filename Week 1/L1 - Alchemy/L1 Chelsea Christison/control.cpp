/*************************************************************
* Author:		Chelsea Christison
* Filename:		display.cpp
* Date Created: 4.12.2017
* Modifications:
**************************************************************/
#include "control.h"

Control::Control(): _current_tile(nullptr)
{
	m_Alchemy = Tile_Board();			//instance of board 
	_flag_highlight = false;			//flag for highlighting a set tile
	_flag_restore_set_tile = false;		//flag for restoring a previously highlighted tile to set: yellow
	_flag_discard = false;				//flag for checking discard count
	FORCE_QUIT = false;					//quit the program 
	game_logic = new GameLogic(this);	//instance for the game logic: placing, score
	_discard_count = 0;					//count of discards 
}

/*************************************************************
* Purpose:
*	This function drives the game. Prints the board, the 
*	instructions, updates/prints score and finally calls
*	findNewSymbol() to begin listening for user input
*	
**************************************************************/
void Control::play()
{
	_current_tile = nullptr; 
	m_Alchemy.printBoard();
	m_Alchemy.printHowToPlay();
	_updateGameInfo();
	findNewSymbol(); 
}

/*************************************************************
* Purpose:
*	This function updates the game information and displays
*	to the conolse. Checks if the board is full, calls for
*	the generation of a new symbol to be placed, and resets 
*	flags before calling _listen_for_move() to get user input; 
*
**************************************************************/
void Control::findNewSymbol()
{
	_updateGameInfo();
	m_Alchemy.checkFullBoard();
	_current_tile = m_Alchemy.getNewSymbolTile();
	_first_move = true; 
	_flag_restore_set_tile = false;
	_flag_discard = false; 
	_flag_highlight = false;
	_look_at_first_tile();
	_listen_for_move(); 
}

Control::~Control()
{
	delete game_logic; 
}

void Control::_updateGameInfo()
{
	m_Alchemy.printGameInfo(game_logic->getScore(), _discard_count);
}

/*************************************************************
* Purpose:
*	This swaps the bracket colors to show user where they're 
*	at within the board. Sets flags where necessary to 
*	ensure highlighted (SET) brackets stay yellow when user
*	leaves.  
*
**************************************************************/
void Control::_swap()
{
	//swap board tile empty symbol with current tile symbol 
	Tile * temp =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);

    temp->setSymbol(*_current_tile->getSymbol());
	temp->printPlayingTile_newSymbol();


	//if previous move set highlight flag
	if (_flag_highlight)
	{
		printTopBottom(_restore_column, _restore_row);
		_flag_highlight = false;
	}
	//if moving to a set tile (YELLOW) 
	if (temp->is_background_set()&& !_first_move )
	{
		//if moving away from a set tile to another set tile
		if(_flag_restore_set_tile)
		{
			_current_tile->printTile_blank();
			printTopBottom(_restore_column, _restore_row);
		}
		//moving to a set tile from an unset tile
		else 
			_current_tile->printTile_blank();
		
		_flag_restore_set_tile = true;	//set restore flag
	}
	//if moving to an unset tile from a set (YELLOW) tile 
	else if (_flag_restore_set_tile)	//ensure we reset if going to an unset tile
	{
		_current_tile->printTile_blank();
		printTopBottom(_restore_column, _restore_row);
		_flag_restore_set_tile = false; 
	}
	//regular moving from unset tile to unset tile 
	else if (_first_move)
		delete _current_tile;
	else
	{
		_current_tile->printTile_blank();
		_flag_restore_set_tile = false; 
	}

	//continuously track restore col and row for printing
	_restore_column = temp->_begin_print_X;
	_restore_row = temp->_begin_print_Y;
	//set current tile to moved tile 
	_current_tile = temp;
}

/*************************************************************
* Purpose:
*	This function merely highlights a tile's brackets if it
*	is currently displaying a set symbol, rather than writing
*	over the symbol with the symbol the user is trying to set
*
**************************************************************/
void Control::_highlight()
{
	Tile * temp =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);

	//print tile with red highlight
	temp->printPlayingTile_newSymbol();
	if (_flag_restore_set_tile)
	{
		_current_tile->printTile_blank();
		printTopBottom(_restore_column, _restore_row);
		_flag_restore_set_tile = false;
	}
	else if (!_flag_highlight)
	{
		_current_tile->printTile_blank();
	}
	else
		printTopBottom(_restore_column, _restore_row);

	//store the reprint - where to begin  print
	_restore_column = temp->_begin_print_X; 
	_restore_row= temp->_begin_print_Y; 

	_flag_highlight = true; 
}

/*************************************************************
* Purpose:
*	This function blinks rapidly to alert the user they can't
*	place a selected tile. 
**************************************************************/
void Control::_blink_error()
{
	Tile * temp =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);
	temp->blink_error(); 
}

/*************************************************************
* Purpose:
*	This function checks if the user is able to move to the
*	tile they wish to move to. 
*
**************************************************************/
bool Control::_check_move()
{
	bool okay_to_move = false; 
	Tile * t =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);

	//check if tile is NOT set, then we can move and copy
	if(!t->is_my_symbol_set() || !t->is_background_set())
	{
		//not set means okay to swap tiles
		okay_to_move = true;
	}
	//if symbol is set, check the next left tile
	return okay_to_move; 
}

/*************************************************************
* Purpose:
*	This function drives the entire game. Waits for user input
*	from the keyboard and executes/does checks. 
**************************************************************/
void Control::_listen_for_move()
{
	char ch;
	do
	{
		ch = getch();
		/* KEY EVENT UP */
		if (ch == UP && !_first_move)
		{
			--_board_tile_row;
			try
			{
				if (_check_move())
					_swap();
				else
					_highlight();
				
			}
			catch(Exception ex)
			{
				++_board_tile_row;
			}
		}
		/* KEY EVENT DOWN */
		else if (ch == LEFT)
		{
			if(_first_move)
			{
				--_board_tile_column;
				if (_check_move())
				{
					_swap();
					_first_move = false;
				}
				else
					_highlight();
			}
			else
			{
				--_board_tile_column; 
				try
				{
					if (_check_move())
						_swap();
					else
						_highlight();
					
				}
				catch (Exception ex)
				{
					++_board_tile_column;
				}
			}

		}
		/* KEY EVENT DOWN */
		else if (ch == DOWN && !_first_move)
		{
			try
			{
				++_board_tile_row; 
				if (_check_move())
					_swap();
				else
					_highlight(); 
			}
			catch(Exception ex)
			{
				--_board_tile_row; 				
			}
		}
		/* KEY EVENT RIGHT */
		else if (ch == RIGHT&& !_first_move)
		{
			try
			{
				++_board_tile_column; 
				if (_check_move())
					_swap();
				else
					_highlight(); 
			}
			catch (Exception ex)
			{
				--_board_tile_column;
			}
		}
		//enter is "e"
		else if(ch == ENTER && !_first_move)
		{
			if (game_logic->checkSet())
			{
				_set_tile();
				--_discard_count;
				m_Alchemy.checkFullRowOrColumn();
				_check_discard();
				findNewSymbol(); 
			}
			else if(game_logic->_im_a_bomb())
			{
				_remove_tile_symbol(); 
				_check_discard();
				findNewSymbol(); 
			}
			else
				_blink_error();

			
		}
		//discard is "q"
		else if(ch == DISCARD)
		{
			_discard(); 
			_updateGameInfo();
			if(!FORCE_QUIT)
				findNewSymbol(); 
		}
		else if(ch == NEXTLVL )
		{
			if (_first_move)
				delete _current_tile; 

			m_Alchemy.advanceLevels();
			play(); 
		}

	} while (ch != EXIT && FORCE_QUIT == false); 
	
}

/*************************************************************
* Purpose:
*	This functions resets the board tile and board column
*	variables to look at the slot to the very left of the
*	spawn box. 
*
**************************************************************/
void Control::_look_at_first_tile()
{
	_board_tile_column = 9; 
	_board_tile_row = 0; 
}

/*************************************************************
* Purpose:
*	This function is used to set the tile to the desired place
*	the user placed it at. 
*	prints. 
**************************************************************/
void Control::_set_tile()
{
	Tile * set_me =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);

	set_me->setSymbol(*_current_tile->getSymbol());
	set_me->getSymbol()->setSetStatus(true); 
	set_me->setBlankTileStatus(false); 
	set_me->printTile();
}

/*************************************************************
* Purpose:
*	This function checks the discard pile and values, ensuring
*	the user doesn't discard more than four times.
*
**************************************************************/
void Control::_check_discard()
{
	if(_discard_count >= DISCARD_COUNT)
	{
		FORCE_QUIT = true; 
	}
	else if (_discard_count <= 0)
	{
		_discard_count = 0; 
	}
}

/*************************************************************
* Purpose:
*	This function prints the top and the bottom brackets at 
*	the desired location. 
*
**************************************************************/
void Control::printTopBottom(int X, int Y)
{
	rlutil::saveDefaultColor(); 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;

	//set position
	cursor.X = X;
	cursor.Y = Y;
	SetConsoleCursorPosition(hOut, cursor);

	rlutil::setColor(rlutil::YELLOW); 
	// print top of tile
	cout << char(213) << char(205) << char(184);
	cursor.Y = cursor.Y + 2;

	SetConsoleCursorPosition(hOut, cursor);

	//bottom
	cout << char(212) << char(205) << char(190) << endl;
	rlutil::resetColor(); 
}

/*************************************************************
* Purpose:
*	this function is called when a user discards a tile. Adds
*	to the discard count and checks if user has gone over
*	the max amount of discards. 
*
**************************************************************/
void Control::_discard()
{
	//are we discarding over a set tile
	try
	{
		if (_check_move())
			_current_tile->printTile_blank();
		else
		{
			Tile * t =
				m_Alchemy.getTile(_board_tile_row, _board_tile_column);
			t->printTile();
		}
		if(_first_move)
			delete _current_tile; 
		
	}
	catch(Exception ex)	//discard before moving
	{
		delete _current_tile;
	}

	_current_tile = nullptr; 
	_flag_discard = true;
	_discard_count++;

	_check_discard(); 
}

/*************************************************************
* Purpose:
*	This function removes the tile symbol when called. 
*
**************************************************************/
void Control::_remove_tile_symbol()
{
	Tile * remove_me =
		m_Alchemy.getTile(_board_tile_row, _board_tile_column);

	remove_me->getSymbol()->clearSymbol();
	remove_me->getSymbol()->setSetStatus(false); 
	remove_me->printTile(); 
}
