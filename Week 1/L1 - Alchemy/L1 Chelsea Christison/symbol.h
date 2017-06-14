/*************************************************************
* Author:			Chelsea Christison
* Filename:			symbol.h
* Date Created:		4.12.2017
* Modifications:
*
* Class: Symbol
*
* Purpose : This class creates a Symbol object to be held in a Tile
*
* Manager functions :
*Array()
* 	Symbol();
*	Symbol(char symbol_type, int level); 
*		creates a random symbol depending on the level 
*	Symbol(const Symbol& copy); 
*	Symbol& operator=(const Symbol& copy); 
*	~Symbol();
*
* Methods:
*   void setToWildSymbol(); 
*	void setSymbol(const char set);
*	Symbol& toggleSet(); 
*	void printSymbol() const;
*	void clearSymbol(); 
*		sets the symbol to a space
*	void setCoord(COORD c); 
*		sets the coordinates where symbol can be printed
*	COORD getCoord(); 
*	bool isSet();
*   void setSetStatus(bool is_set); 
*	unsigned char getChar(); 
*	colors getColor(); 
*	
*************************************************************************/
#ifndef SYMBOL_H
#define SYMBOL_H
#include <windows.h>
#include <ostream>
using std::ostream; 
#include <string>
using std::string; 
#include "rlutil.h"

const unsigned char SYM_STYLE_1 = 149;
const unsigned char SYM_STYLE_2 = 224;
const unsigned char SYM_STYLE_3 = 228;
const unsigned char SYM_STYLE_4 = 229;
const unsigned char SYM_STYLE_5 = 227;
const unsigned char SYM_STYLE_6 = 225;

const unsigned char WILD = 240; 
const unsigned char BOMB = 88; //used to remove a symbol

class Symbol
{
public:
	friend class Control; 
	enum colors{LIGHTCYAN, YELLOW, MAGENTA, LIGHTGREEN, GREEN, BROWN, LIGHTBLUE, WHITE, LIGHTRED, LIGHTMAGENTA};

	Symbol();
	Symbol(char symbol_type, int level); 
	Symbol(const Symbol& copy); 
	Symbol& operator=(const Symbol& copy); 
	~Symbol();

	void setToWildSymbol(); 
	void setSymbol(const char set);
	Symbol& toggleSet(); 
	void printSymbol() const;
	void clearSymbol(); 
	void setCoord(COORD c); 
	COORD getCoord(); 
	bool isSet();
	void setSetStatus(bool is_set); 
	unsigned char getChar(); 
	colors getColor(); 

private:	
	unsigned char m_symbol;
	colors m_color; 
	bool m_set; 
	COORD m_symbol_coord;
	void curPos(int x, int y);
};
#endif;