#include "gamelogic.h"
#include "tile_board.h"

GameLogic::GameLogic() :c(nullptr), _score(0)
{
}

GameLogic::GameLogic(Control * control):c(control), _score(0)
{}

bool GameLogic::checkSet()
{
	int col = 0;
	int row = 0;
	bool _ok_left = false; 
	bool _ok_right= false;
	bool _ok_up = false;
	bool _ok_down = false;
	bool _empty_island = true; 
	int _multiplier = 0; 

	//check if we are setting on top of a set piece 
	if (_empty(c->_board_tile_column, c->_board_tile_row))
	{
		if (_left_exists())
		{
			//if left exists, then it's okay to view
			row = c->_board_tile_row;
			col = c->_board_tile_column - 1;

			//if left tile is NOT empty, compare my place ability 
			if (!_empty(col, row))
			{
				_empty_island = false;
				//if left tile isn't a WILD check other conditions 
				if (_im_wild())
					_ok_left = true;
				else if (!_is_wild(col, row))
					_ok_left = _same_color(col, row) || _same_symbol(col, row);
				else //it is a WILD? then it's okay to place myself here
					_ok_left = true;

				if (_ok_left)
					_multiplier++;
			}
			else //left tile IS empty, okay to place 
				_ok_left = true; //since it doesn't exist oky to place
		}
		else // left doesn't exist, and shouldn't be accounted for (I.E. EDGE) 
			_ok_left = true;

		if (_right_exists())
		{
			row = c->_board_tile_row;
			col = c->_board_tile_column + 1;

			//if right is NOT empty - compare 
			if (!_empty(col, row))
			{
				_empty_island = false;
				if (_im_wild())
					_ok_right = true;
				else if (!_is_wild(col, row))
					_ok_right = _same_color(col, row) || _same_symbol(col, row);
				else //otherwise, place 
					_ok_right = true;

				if (_ok_right)
					_multiplier++;
			}
			else //otherwise, place 
				_ok_right = true;
		}
		else //right doesn't exist (EDGE) ok to place
			_ok_right = true;

		if (_up_exists())
		{
			col = c->_board_tile_column;
			row = c->_board_tile_row - 1;

			if (!_empty(col, row))
			{
				_empty_island = false;
				if (_im_wild())
					_ok_up = true;
				else if (!_is_wild(col, row))
					_ok_up = _same_color(col, row) || _same_symbol(col, row);
				else
					_ok_up = true;

				if (_ok_up)
					_multiplier++;
			}
			else
				_ok_up = true;
		}
		else
			_ok_up = true;

		if (_down_exists())
		{
			col = c->_board_tile_column;
			row = c->_board_tile_row + 1;

			if (!_empty(col, row))
			{
				_empty_island = false;

				if (_im_wild())
					_ok_down = true;
				else if (!_is_wild(col, row))
					_ok_down = _same_color(col, row) || _same_symbol(col, row);
				else
					_ok_down = true;

				if (_ok_down)
					_multiplier++;
			}
			else
				_ok_down = true;
		}
		else
			_ok_down = true;
	}
	else
		return false; //placing on a set piece, SO NO 

	if (_empty_island)
		return false; 
	
	//if its overall okay to place the tile down 
	if (_ok_left && _ok_right && _ok_up && _ok_down)
		_determine_score(_multiplier); 

	return _ok_left && _ok_right && _ok_up && _ok_down;
}

int GameLogic::getScore()
{
	return _score; 
}

GameLogic::~GameLogic()
{
}

bool GameLogic::_left_exists()
{
	//look at tile on the left
	return (c->_board_tile_column - 1 < COLUMNS
		&& (c->_board_tile_column - 1 > -1)
		&& (c->_board_tile_row < ROWS && c->_board_tile_row > -1));
}

bool GameLogic::_right_exists()
{
	//look at tile on the right
	return ((c->_board_tile_column + 1 < COLUMNS) 
			&& (c->_board_tile_column + 1 > -1)
			&& (c->_board_tile_row < ROWS) 
			&& (c->_board_tile_row > -1));
}

bool GameLogic::_up_exists()
{
	//look at tile above
	return ((c->_board_tile_column < COLUMNS 
			&& c->_board_tile_column > - 1)
			&& (c->_board_tile_row - 1 < ROWS 
			&& c->_board_tile_row - 1 > -1));
}

bool GameLogic::_down_exists()
{
	//look at tile below
	return ((c->_board_tile_column < COLUMNS) 
			&& (c->_board_tile_column > -1)
			&& (c->_board_tile_row + 1 < ROWS)
			&& (c->_board_tile_row + 1 > -1));
}

bool GameLogic::_is_wild(int X, int Y)
{
	Tile * t =
		c->m_Alchemy.getTile(Y, X);
	return t->getSymbol()->getChar() == WILD;
}

bool GameLogic::_same_color(int X, int Y)
{

	Tile * t =
		c->m_Alchemy.getTile(Y, X);
	return t->getSymbol()->getColor() == c->_current_tile->getSymbol()->getColor();
}

bool GameLogic::_im_wild()
{
	return c->_current_tile->getSymbol()->getChar() == WILD; 
}

bool GameLogic::_im_a_bomb()
{
	return c->_current_tile->getSymbol()->getChar() == BOMB;
}

bool GameLogic::_is_unset(int X, int Y)
{
	Tile * t =
		c->m_Alchemy.getTile(Y, X);
	return t->getSymbol()->isSet();		
}

bool GameLogic::_empty(int X, int Y)
{
	Tile * t =
		c->m_Alchemy.getTile(Y, X);
	return !(t->is_my_symbol_set());
}

bool GameLogic::_is_edge()
{
	//check if the place to set is actually an edge
	return c->_board_tile_column == COLUMNS - 1 ||
		c->_board_tile_row == ROWS - 1 || c->_board_tile_row == 0
		|| c->_board_tile_column == 0; 

}

bool GameLogic::_same_symbol(int X, int Y)
{
	Tile * t =
		c->m_Alchemy.getTile(Y, X);
	return t->getSymbol()->getChar() == c->_current_tile->getSymbol()->getChar();
}

void GameLogic::_determine_score(int multiplier)
{
	_score += (5 * multiplier);
}
