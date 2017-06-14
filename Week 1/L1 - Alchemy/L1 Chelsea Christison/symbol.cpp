/*************************************************************
* Author:		Todd Breedlove
* Filename:		Lab1.cpp
* Date Created:	12/17/96
* Modifications:	1/5/01 – Corrected problem names with spaces
*  			3/29/11 – Corrected A’s counting issue
**************************************************************/

#include "symbol.h"
#include <iostream>
#include "control.h"

Symbol::Symbol() : m_symbol(' '), m_set(false), m_color(colors::WHITE)
{
}

Symbol::Symbol(char symbol_type, int level) : m_symbol(symbol_type), m_set(false)
{
	int r = level + 2;

	int random_color = rand() % r;	//0 to 6 OR 0 - 7

	switch (random_color)
	{
	case 0:
		m_color = colors::LIGHTCYAN; 
		break;
	case 1:
		m_color = colors::YELLOW;
		break;
	case 2:
		m_color = colors::MAGENTA;
		break;
	case 3:
		m_color = colors::LIGHTGREEN;
		break;
	case 4:
		m_color = colors::GREEN; 
		break;
	case 5:	//lowermost
		m_color = colors::BROWN; 
		break;
	case 6: //upper most _level
		m_color = colors::LIGHTBLUE;
		break;
	case 7:
		m_color = colors::WHITE;
		break;
	case 8:
		m_color = colors::LIGHTRED; 
		break;
	case 9:
		m_color = colors::LIGHTMAGENTA; 
		break;
	default:;
	}

	if (m_symbol == WILD)
		m_color = colors::WHITE;
	else if (m_symbol == BOMB)
		m_color = colors::LIGHTRED; 

}
Symbol::Symbol(const Symbol& copy): m_symbol(copy.m_symbol), m_color(copy.m_color), m_set(copy.m_set)
{}

Symbol& Symbol::operator=(const Symbol& copy)
{
	if(this != &copy)
	{
		m_symbol = copy.m_symbol; 
		m_color = copy.m_color;
		m_set = copy.m_set; 
		m_symbol_coord = copy.m_symbol_coord; 
	}
	return *this; 
}

Symbol::~Symbol()
{
	m_symbol = '\0';
}

void Symbol::setToWildSymbol()
{
	m_color = colors::WHITE; 
	this->m_symbol = WILD;
	m_set = true; 
}

void Symbol::setSymbol(const char set)
{
	m_symbol = set; 
}

Symbol& Symbol::toggleSet()
{
	this->m_set = !m_set; 
	return *this; 
}

void Symbol::printSymbol() const
{
	rlutil::saveDefaultColor();		//save	

	
	switch (m_color)
	{
	case LIGHTCYAN:
		rlutil::setColor(rlutil::LIGHTCYAN);
		break;
	case YELLOW:
		rlutil::setColor(rlutil::YELLOW);
		break;
	case MAGENTA:
		rlutil::setColor(rlutil::MAGENTA);
		break;
	case LIGHTGREEN:
		rlutil::setColor(rlutil::LIGHTGREEN);
		break;
	case GREEN:
		rlutil::setColor(rlutil::GREEN);
		break;
	case BROWN:
		rlutil::setColor(rlutil::BROWN);
		break;
	case LIGHTBLUE:
		rlutil::setColor(rlutil::LIGHTBLUE);
		break; 
	case WHITE:
		rlutil::setColor(rlutil::WHITE); 
		break; 
	case LIGHTRED:
		rlutil::setColor(rlutil::LIGHTRED);
		break; 
	case LIGHTMAGENTA:
		rlutil::setColor(rlutil::LIGHTMAGENTA);
		break; 
	default:;
	}
	std::cout << m_symbol;
	rlutil::resetColor();	//reset background to black
}

void Symbol::clearSymbol()
{
	m_symbol = ' '; 
}

void Symbol::setCoord(COORD c)
{
	m_symbol_coord = c;
}

COORD Symbol::getCoord()
{
	return	m_symbol_coord;
}

bool Symbol::isSet()
{
	return m_set; 
}

void Symbol::setSetStatus(bool is_set)
{
	m_set = is_set; 
}

unsigned char Symbol::getChar()
{
	return m_symbol; 
}

Symbol::colors Symbol::getColor()
{
	return m_color; 
}

void Symbol::curPos(int x, int y)
{
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hStdout, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hStdout, csbiInfo.dwCursorPosition);
}
