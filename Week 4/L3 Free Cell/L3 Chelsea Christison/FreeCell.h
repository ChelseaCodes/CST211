/************************************************************************
* Class: FreeCell
*
* Purpose:
*	This class puts together all the components for the game FreeCell
*
* Manager functions:
* 	FreeCell()
* 	~FreeCell()
* Methods:
*	Play()
*		runs the game
*	Display()
*	DisplayHowtoPlay()
*	Displayerror(string error)
*	UserInput()
*		get userinput 
*	m_check_range(int n, char type)
*		check if given n is in range of the type of move
*	m_check_card_placement(Card before, Card after)
*		check if two cards are able to be placed next to one another
*	m_Play_to_Free(int play_index)
*		moving from playarea to freecell
*	m_Play_to_Home(int play_index)
*		moving from playarea to homecells
*	m_Play_to_Play(int play_index_1, int play_index_2)
*		moving from playarea to another column in playarea
*	m_Free_to_Home(int free_index)
*		moving from freecell to homecells
*	m_Free_to_Play(int free_index, int play_index)
*		moving from freecell to playarea
*	m_get_row_to_start()
*		retreive the row to look at if moving x number of cards at a time
*************************************************************************/
#ifndef FREECELL_H
#define FREECELL_H
#include "string"
using std::string; 

#include "lstack.h"
#include "freecells.h"
#include "homecells.h"
#include "playcards.h"

const int TITLE_X = 36; 
const int TITLE_Y = 2; 
const int USERINPUT_X = X_COORD; 
const int USERINPUT_Y = Y_COORD + 20; 
const int HOWTO_X = USERINPUT_X - 5; 
const int HOWTO_Y = USERINPUT_Y + 3;
const int ERROR_X = USERINPUT_X; 
const int ERROR_Y = HOWTO_Y + 15;
const int MOVES = 103; 
const int ROW_INPUTS = 9; 
static char * m_auto_play_1[] = { "p1h", "p5h", "p3f", "p3h", "f0h","p0p4", "p0p6", "p6p2", "p6p4", "p0p4", "p6p2", "p0p2", "p6p4", "p0p4",
								"p6f","p6h", "p0f", "p0h", "f0h", "f0h", "p4h", "p2h", "p1p0", "p5f", "p5p0", "p1f", "p1p0", "p7f", "p7p3", "f0p6",
								"f0p6", "p7p6", "p7p0", "p4h", "p2h", "p2p7", "p1p5","p4h", "p7h", "p4h", "p7h", "p4h", "p7f", "p7f", "p7h", "f2h",
								"f0p7", "p1p0", "p1h", "p0h" ,"p0h", "p3p1", "p5h", "p6h", "p0h", "p1h", "p6h", "p7h","p0f",
								"p0h", "p3p6", "p3p0", "p3p5", "p5f", "p5p6", "p3p5", "p4f", "f3p5", "p2p5", "p5p3", "f0p5", "p4p5", "p2p5",
								"p2p4", "f0p1", "p0p1", "p2f", "p2f", "f0p6", "p2h", "f1h", "f0h", "p4p3", "p4p5", "p4p3", "p4h", "p3h", "p5h", "p3h", "p5h",
								"p3h", "p5h", "p3h", "p3h", "p5h", "p3h", "p5h", "p3h", "p6h", "p6h", "p1h", "p6h", "p1h"};

static int m_auto_row_input[] = { 5, 5, 6, 4, 2, 1, 3 };
static int row_input_i = 0; 

const int auto2 = 24; 

class FreeCell
{
	friend class FreeCells;
	friend class HomeCells; 
	friend class PlayCards; 
public:
	FreeCell(); 
	~FreeCell();
	void Play(); 
private:
	void Display(); 
	void DisplayHowToPlay(); 
	void DisplayError(string error); 
	void UserInput(); 
	FreeCells m_free_cells; 
	HomeCells m_home_cells; 
	PlayCards m_play_area; 
	int m_p_inputs[MAX_COL];	//0 - 7
	int m_f_inputs[MAX];		//0 - 3
	int m_h_inputs[MAX];		//0 - 3
	bool m_error_flag;
	string m_saved_error; 
	bool m_check_range(int n, char type);
	bool m_check_card_placement(Card before, Card after); 
	void m_Play_to_Free(int play_index);
	void m_Play_to_Home(int play_index);
	void m_Play_to_Play(int play_index_1, int play_index_2); 
	void m_Free_to_Home(int free_index);
	void m_Free_to_Play(int free_index, int play_index); 
	int m_get_row_to_start();
	bool m_check_win(); 
};
#endif