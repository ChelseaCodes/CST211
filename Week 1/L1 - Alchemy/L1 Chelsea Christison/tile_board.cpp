#include"tile_board.h"
#include "control.h"

Tile_Board::Tile_Board(): _level(5)
{
	m_tile_board = Array2D<Tile>(ROWS, COLUMNS);
}

void Tile_Board::printNewTileBox()
{
	HANDLE mOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(mOut, m_top_right_of_board);
	cout << char(169) << ' ' << char(170);
	m_symbol_placement.X = m_top_right_of_board.X + 1; 
	m_symbol_placement.Y = m_top_right_of_board.Y + 1; 
}

void Tile_Board::printBoard()
{
	int X = 0;
	int Y_Start = 0;
	int Y = 0;

	m_top_right_of_board.X = TILE_WIDTH * COLUMNS;
	m_top_right_of_board.Y = Y_Start;
	m_bottom_left_of_board.X = TILE_WIDTH * COLUMNS;
	m_bottom_left_of_board.Y = Y_Start + (TILE_LENGTH * ROWS);

	m_tile_board[ROW_MID][COL_MID].setWildSymbol();
	
	for(int row = 0; row < ROWS; row++)
	{
		for(int col = 0; col < COLUMNS; col++)
		{
			Y = Y_Start; 
			m_tile_board[row][col]._begin_print_Y = Y;
			m_tile_board[row][col]._begin_print_X = X;
			m_tile_board[row][col].printTile(); 
			X += TILE_WIDTH; 
		}
		Y_Start += TILE_LENGTH; 
		X = 0; 
	}
}

void Tile_Board::printHowToPlay()
{
	//save the original coordinates
	COORD restore_top_right = m_top_right_of_board; 

	//create handle 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	rlutil::saveDefaultColor(); 

	//place how to header
	m_top_right_of_board.X += 14;

	rlutil::setColor(rlutil::LIGHTMAGENTA);
	SetConsoleCursorPosition(hOut,m_top_right_of_board);
	cout << "  = How To Play Alchemy =";

	m_top_right_of_board.Y++; 
	SetConsoleCursorPosition(hOut, m_top_right_of_board); 
	cout << "W/A/S/D - navigate symbol on board ";

	m_top_right_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "e - place symbol in desired spot ";

	m_top_right_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "q - discard current symbol";

	m_top_right_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "r - quit game";

	m_top_right_of_board.X -= 7; 
	m_top_right_of_board.Y += 3;

	rlutil::setColor(rlutil::LIGHTBLUE);
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "Can only place tiles of like color OR symbol";

	m_top_right_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "*triple equal* - WILD; place by any set tile";

	m_top_right_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_top_right_of_board);
	cout << "X - BOMB; remove any one set tile";

	rlutil::resetColor(); 
	m_top_right_of_board = restore_top_right; 
}

void Tile_Board::printGameInfo(int score, int discard_strikes)
{
	//save the original coordinates
	COORD restore_bottom_left = m_bottom_left_of_board;

	//create handle 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	rlutil::saveDefaultColor();

	m_bottom_left_of_board.X += 7; 
	m_bottom_left_of_board.Y -= 7; 
	SetConsoleCursorPosition(hOut, m_bottom_left_of_board); 

	rlutil::setColor(rlutil::CYAN); 
	cout << "your score: " << score;

	m_bottom_left_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_bottom_left_of_board);
	cout << "discard strikes: " << discard_strikes; 

	m_bottom_left_of_board.Y++;
	SetConsoleCursorPosition(hOut, m_bottom_left_of_board);
	cout << "4 strikes = END GAME";

	m_bottom_left_of_board.Y += 2;
	SetConsoleCursorPosition(hOut, m_bottom_left_of_board);
	cout << "n - auto next _level";

	rlutil::resetColor();
	m_bottom_left_of_board = restore_bottom_left; 
}

void Tile_Board::printSuccess()
{
	//save the original coordinates
	COORD restore_bottom_left = m_bottom_left_of_board;

	//create handle 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	rlutil::saveDefaultColor();

	m_bottom_left_of_board.X += 7;
	m_bottom_left_of_board.Y -= 2;
	SetConsoleCursorPosition(hOut, m_bottom_left_of_board);
	rlutil::setColor(rlutil::LIGHTGREEN);
	cout << "NEXT LEVEL"; 

	rlutil::resetColor();
	m_bottom_left_of_board = restore_bottom_left;

}

Tile_Board::~Tile_Board()
{
}

Tile* Tile_Board::getTile(int row, int column)
{
	return &m_tile_board[row][column];
}

void Tile_Board::setTile(Symbol& symbol, int row, int column)
{
	m_tile_board[row][column].setSymbol(symbol);
}

void Tile_Board::placePlaySymbol(Symbol * symbol)
{
	//create handle 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, m_symbol_placement);
	symbol->printSymbol(); 
	symbol->setCoord(m_symbol_placement); 
}

void Tile_Board::updateSymbolPlacement(Symbol* s)
{
	//create handle 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(hOut, s->getCoord());
	s->printSymbol();
}

void Tile_Board::checkFullRowOrColumn()
{
	bool clear_row = true; 
	bool clear_column = true; 
	int col_to_clear = 0;
	int row_to_clear = 0;

	//first check if any column is full
	for(int col = 0; col < COLUMNS ; col++)
	{
		clear_column = true;
		for(int row = 0; row < ROWS && clear_column; row++)
		{
			Tile * temp =
				&m_tile_board[row][col];
			if (temp->is_my_symbol_set())
			{
				col_to_clear = col;
			}
			else
				clear_column = false; 
		}
		if (clear_column)
		{
			clearColumn(col_to_clear);
		}
	}

	//then check if any row is full
	for (int row = 0; row < ROWS ; row++)
	{
		clear_row = true; 
		for (int col = 0; col < COLUMNS && clear_row; col++)
		{
			Tile * temp =
				&m_tile_board[row][col];
			if (temp->is_my_symbol_set())
			{
				row_to_clear = row; 
			}
			else
				clear_row = false;
		}
		if(clear_row)
		{
			clearRow(row_to_clear);
		}
	}
}

void Tile_Board::clearRow(int row)
{
	for(int col = 0; col < COLUMNS; col++)
	{
		Tile * temp =
			&m_tile_board[row][col]; 

		temp->getSymbol()->clearSymbol();
		temp->getSymbol()->setSetStatus(false);
		temp->printTile(); 
	}
}

void Tile_Board::clearColumn(int column)
{
	for (int row = 0; row < ROWS; row++)
	{
		Tile * temp =
			&m_tile_board[row][column];

		temp->getSymbol()->clearSymbol();
		temp->getSymbol()->setSetStatus(false); 
		temp->printTile();
	}
}

void Tile_Board::checkFullBoard()
{
	//_check_full_board_works(); 

	bool full_board = true; 
	for (int row = 0; row < ROWS && full_board; row++)
	{
		for (int col = 0; col < COLUMNS && full_board; col++)
		{
			Tile * temp =
				&m_tile_board[row][col];
			if (!temp->is_background_set())
			{
				full_board = false; 
			}
				
		}
	}
	if (full_board)
	{
		advanceLevels();
	}
}

void Tile_Board::advanceLevels()
{
	if(_level < 6)
	{
		_clearBoard();
		printSuccess(); 
		_level = 6; 
	}
}

void Tile_Board::_check_full_board_works()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			m_tile_board[row][col].setBlankTileStatus(false);
			m_tile_board[row][col].getSymbol()->setSetStatus(true);
		}
	}
}

void Tile_Board::_clearBoard()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLUMNS; col++)
		{
			m_tile_board[row][col].setBlankTileStatus(true);
			m_tile_board[row][col].getSymbol()->clearSymbol();
			m_tile_board[row][col].getSymbol()->setSetStatus(false);
		}
	}
}

Tile* Tile_Board::getNewSymbolTile()
{
	m_new_symbol_box = new Tile();
	m_new_symbol_box->generateRandomTile(_level);

	m_new_symbol_box->_begin_print_X = m_top_right_of_board.X;
	m_new_symbol_box->_begin_print_Y = m_top_right_of_board.Y;
	m_new_symbol_box->m_symbol_placement.X = m_top_right_of_board.X + 1;
	m_new_symbol_box->m_symbol_placement.Y = m_top_right_of_board.Y + 1;

	m_new_symbol_box->printPlayingTile_newSymbol();

	return m_new_symbol_box; 
}
