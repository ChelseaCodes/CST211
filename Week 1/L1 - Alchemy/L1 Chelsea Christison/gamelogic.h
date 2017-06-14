#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include  "control.h"

class GameLogic
{
	friend class Control; 
public:
	GameLogic(); 
	GameLogic(Control * control); 
	bool checkSet(); 
	int getScore(); 
	~GameLogic();
private:
	int _score; 
	Control * c; 
	bool _left_exists();
	bool _right_exists();
	bool _up_exists();
	bool _down_exists();
	bool _is_wild(int X, int Y);
	bool _same_color(int X, int Y);
	bool _im_wild();
	bool _im_a_bomb(); 
	bool _is_unset(int X, int Y); 
	bool _empty(int X, int Y); 
	bool _is_edge(); 
	bool _same_symbol(int X, int Y);
	void _determine_score(int multiplier); 
};
#endif