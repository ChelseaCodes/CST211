/*************************************************************
* Author:		Chelsea Christison
* Filename:		display.h
* Date Created: 4.13.2017
* Modifications:
**************************************************************/
#ifndef CONTROL_H
#define CONTROL_H
#include "tile_board.h"
#include "gamelogic.h"

const char DISCARD = 'q';
const char ENTER = 'e'; 
const char UP = 'w';
const char LEFT = 'a';
const char DOWN = 's';
const char RIGHT = 'd';
const char EXIT = 'r'; 
const char NEXTLVL = 'n'; 


static int DISCARD_COUNT = 4; 

class Control
{
	friend class Symbol; 
	friend class GameLogic; 
public:
	Control(); 
	void play(); 
	void findNewSymbol();
	~Control(); 
private:
	Tile_Board m_Alchemy;
	Tile * _current_tile; 
	GameLogic  * game_logic;
	bool _flag_discard; 
	bool FORCE_QUIT; 
	int _discard_count; 
	int _board_tile_row; 
	int _board_tile_column; 
	bool _first_move; 
	bool _flag_restore_set_tile; 
	bool _flag_highlight; //used for reprinting after highlighting 
	int  _restore_row;
	int _restore_column;
	void _updateGameInfo(); 
	void _swap();
	void _highlight(); 
	void _blink_error(); 
	bool _check_move();
	void _listen_for_move(); 
	void _look_at_first_tile(); 
	void _set_tile(); 
	void _check_discard(); 
	void printTopBottom(int X, int Y);
	void _discard();
	void _remove_tile_symbol(); 
};
#endif