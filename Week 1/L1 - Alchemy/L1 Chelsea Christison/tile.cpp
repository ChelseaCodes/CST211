/*************************************************************
* Author:			Chelsea Christison
* Filename:			tile.cpp
* Date Created:		4.12.2017
* Modifications:
**************************************************************/
#include  "tile.h"
#include "tile_board.h"


Tile::Tile() : m_blank_tile(true)
{
	m_tile_symbol = Symbol(); 
}

Tile::Tile(const Tile& copy) : m_tile_symbol(copy.m_tile_symbol)
{}

Tile& Tile::operator=(const Tile& copy)
{
	if (this != &copy)
	{
		m_tile_symbol = copy.m_tile_symbol;
		m_blank_tile = copy.m_blank_tile;
		m_symbol_placement = copy.m_symbol_placement;
		_begin_print_X = copy._begin_print_X;
		_begin_print_Y = copy._begin_print_Y;
	}
	return *this;
}

/*************************************************************
* Purpose: 
*	This function is used to generate a random symbol 
*	depending on the level, which is passed in. 

**************************************************************/
void Tile::generateRandomTile(int level)
{
	int r = level + 2; 
	int random_symbol = rand() % r ;	
	random_symbol = rand() % r;
	random_symbol = rand() % r;

	switch (random_symbol)
	{
		case 0:
			random_symbol = SYM_STYLE_1; 
			break;
		case 1:
			random_symbol = SYM_STYLE_2; 
			break; 
		case 2:
			random_symbol = SYM_STYLE_3;
			break; 
		case 3:
			random_symbol = SYM_STYLE_4;
			break; 
		case 4:
			random_symbol = SYM_STYLE_5;
			break;
		case 5:
			random_symbol = WILD;
			break; 
		case 6:
			random_symbol = BOMB;
			break; 
		case 7:
			random_symbol = SYM_STYLE_6;	//one _level up 
			break; 
		default:;
	}		

	m_tile_symbol = Symbol(random_symbol, level); //should create a random color for symbol
}

Symbol* Tile::getSymbol() 
{
	return &m_tile_symbol; 
}

void Tile::printTile()
{
	rlutil::saveDefaultColor(); 
	
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE); 
	COORD cursor; 

	//set position
	cursor.X = _begin_print_X; 
	cursor.Y = _begin_print_Y; 
	SetConsoleCursorPosition(hOut, cursor); 

	if (!m_blank_tile)
		rlutil::setColor(rlutil::YELLOW);
	// print top of tile
	printTileTop(); 
	cursor.Y++;
	rlutil::resetColor(); 
	//move to print middle
	SetConsoleCursorPosition(hOut, cursor); 

	m_symbol_placement.X = cursor.X + 1; //set where a symbol would be 
	m_symbol_placement.Y = cursor.Y; //set where symbol would be
	
	//print middle of tile
	printTileMiddle(); 
	cursor.Y++;
	//move to print bottom
	SetConsoleCursorPosition(hOut, cursor); 

	if (!m_blank_tile)
		rlutil::setColor(rlutil::YELLOW);
	//bottom
	printTileBottom(); 	

	rlutil::resetColor(); 
}

void Tile::printPlayingTile_newSymbol()
{
	rlutil::saveDefaultColor(); 
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;
	//set position
	cursor.X = _begin_print_X;
	cursor.Y = _begin_print_Y;
	SetConsoleCursorPosition(hOut, cursor);

	rlutil::setColor(rlutil::RED); 
	// print top of tile
	printTileTop();
	rlutil::resetColor(); 
	cursor.Y++; 
	//move to print middle
	SetConsoleCursorPosition(hOut, cursor); 

	m_symbol_placement.X = cursor.X + 1; //set where a symbol would be 
	m_symbol_placement.Y = cursor.Y; //set where symbol would be

	//print middle of tile
	printTileMiddle();
	cursor.Y++; 
	//move to print bottom
	SetConsoleCursorPosition(hOut, cursor); 

	rlutil::setColor(rlutil::RED);
	//bottom
	printTileBottom();
	rlutil::resetColor();
}

void Tile::printTile_blank()
{
	rlutil::saveDefaultColor();
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursor;

	//set position
	cursor.X = _begin_print_X;
	cursor.Y = _begin_print_Y;
	SetConsoleCursorPosition(hOut, cursor);

	// print top of tile
	printTileTop();
	cursor.Y++;
	//move to print middle
	SetConsoleCursorPosition(hOut, cursor);

	m_symbol_placement.X = cursor.X + 1; //set where a symbol would be 
	m_symbol_placement.Y = cursor.Y; //set where symbol would be
									 //print middle of tile
	printBlank();
	cursor.Y++;
	//move to print bottom
	SetConsoleCursorPosition(hOut, cursor);

	//bottom
	printTileBottom();
	rlutil::resetColor(); 
}

void Tile::blink_error()
{
	for (int i(0); i < 2; i++)
	{
		printTile();
		Sleep(100);
		printPlayingTile_newSymbol();
		Sleep(100); 
	}
}

//used to set a tile symbol to a wild
void Tile::setWildSymbol()
{
	m_tile_symbol.setToWildSymbol();
	m_blank_tile = false; //no longer blank
}

void Tile::setSymbol(Symbol& symbol)
{
	m_tile_symbol = symbol;
}

bool Tile::is_my_symbol_set()
{
	return m_tile_symbol.isSet(); 
}

bool Tile::is_background_set()
{
	//if it's not a blank tile then it's not 
	//a set background will be false
	//if it is a blank time, the background is set
	// = true
	return m_blank_tile == false; 
}

Tile::~Tile()
{}

Tile& Tile::operator=(const Symbol& copy)
{
	this->m_tile_symbol = copy; 
	return *this; 
}

void Tile::setBlankTileStatus(bool is_blank)
{
	m_blank_tile = is_blank;
}

void Tile::printTileTop()
{
	//top
	cout << char(213) << char(205) << char(184);
}

void Tile::printTileMiddle()
{
	//middle 
	//cout << char(179);
	cout << " ";
	m_tile_symbol.printSymbol();
	//cout << char(179);
	cout << " ";
}

void Tile::printTileBottom()
{
	cout << char(212) << char(205) << char(190);
}

void Tile::printBlank()
{
	cout << "   ";
}

