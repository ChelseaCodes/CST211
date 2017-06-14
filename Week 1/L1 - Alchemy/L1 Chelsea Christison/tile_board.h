/*************************************************************
* Author:		Chelsea Christison
* Filename:		tile_board.h
* Date Created: 4.13.2017
* Modifications:
**************************************************************/
#ifndef TILE_BOARD_H
#define TILE_BOARD_H
#include"array2D.h"
#include "tile.h"
#include "row.h"
 
const int ROWS = 8;		//num of rows for board
const int COLUMNS = 9;	//num of columns for board
const int ROW_MID = 3;	//row where middle tile is - for WildSymbol
const int COL_MID = 4;	//col where middle tile is 

class Tile_Board
{
public:
	Tile_Board(); 
	//copy c'tor
	//op=
	~Tile_Board();

	//printing 
	void printNewTileBox(); 
	void printBoard(); 
	void printHowToPlay();
	void printGameInfo(int score, int discard_strikes); 
	void printSuccess();

	//setters getters
	Tile* getTile(int row, int column); 
	void setTile(Symbol & symbol, int row, int column); 
	void placePlaySymbol(Symbol * symbol); 
	void updateSymbolPlacement(Symbol* s);
	Tile * getNewSymbolTile();

	//checks
	void checkFullRowOrColumn(); 
	void clearRow(int row); 
	void clearColumn(int column); 
	void checkFullBoard(); 
	void advanceLevels(); 

		
private:
	Array2D<Tile> m_tile_board; 
	Tile * m_new_symbol_box; 
	COORD m_top_right_of_board; 
	COORD m_bottom_left_of_board;
	COORD m_symbol_placement; 
	void _check_full_board_works(); 
	void _clearBoard(); 
	int _level; 
};
#endif
