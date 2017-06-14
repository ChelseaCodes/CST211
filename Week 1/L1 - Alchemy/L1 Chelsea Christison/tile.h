/*************************************************************
* Author:			Chelsea Christison
* Filename:			tile.h
* Date Created:		4.12.2017
*
* Class: Tile 
*
* Purpose : This class creates a Tile which holds a Symbol object. 
*	Tiles are used when making thee 2D Array in the Tile_Board class.
*
* Manager functions :
*Array()
* 	Tile();
* 		blank tile by default, creates an instance of Symbol
*	Tile(const Tile& copy);
*	Tile& operator=(const Tile&copy);
*	Tile& operator=(const Symbol& copy);
*	~Tile();
*
* Methods:
*   void generateRandomTile(int level);
*		generates a random tile using the current level 
*	void blink_error(); 
*		blinks at the user when a tile cant be placed *	
*	Symbol* getSymbol();
*	void setWildSymbol()
*		used to set the middlemost tile to a wild 
*	void setSymbol(Symbol& symbol); 
*	bool is_my_symbol_set(); 
*		returns if the calling tile's Symbol is currently set
*	bool is_background_set();
*		returns if the tile is blank. if it's not then background is set
*	void setBlankTileStatus(bool is_blank); *	 
*	void printTile();
*		prints the tile with it's assigned symbol
*	void printPlayingTile_newSymbol();
*		prints the tile but with red brackets to show user where they are
*	void printTile_blank();
*		prints a set tile with yellow brackets and a blank Symbol
*	
*************************************************************************/

#ifndef TILE_H
#define TILE_H
#include "symbol.h"
#include <iostream>
using std::cout; 
using std::endl; 

#include "rlutil.h"

const int TILE_WIDTH = 3; 
const int TILE_LENGTH = 3; 

class Tile
{
public:
	//enum of symbols, assigned to their ASCII equivalents. Will use rand() to pick randomly
	enum symbol_choice { S_1 = 1, S_2, S_3, S_4, S_5, S_6 };

	Tile();
	Tile(const Tile& copy);
	Tile& operator=(const Tile&copy);
	Tile& operator=(const Symbol& copy);
	~Tile();

	//randomized tile generator
	void generateRandomTile(int level);
	
	//blink error animation 
	void blink_error(); 

	//setters getters
	Symbol* getSymbol();
	void setWildSymbol(); 
	void setSymbol(Symbol& symbol); 
	bool is_my_symbol_set(); 
	bool is_background_set();
	void setBlankTileStatus(bool is_blank); 

	//printing 
	void printTile();
	void printPlayingTile_newSymbol();
	void printTile_blank();

	//public vars
	COORD m_symbol_placement;	//coords where a symbol can be placed
	int _begin_print_X; 
	int _begin_print_Y; 
private:
	Symbol m_tile_symbol;
	bool m_blank_tile; 
	void printTileTop(); 
	void printTileMiddle(); 
	void printTileBottom(); 
	void printBlank();
};
#endif
