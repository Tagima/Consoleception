#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

#include "consoleception/game_base.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

class MineSweeper : public GameBase
{
public:
	MineSweeper(int t_width, int t_height, int t_num_mines);
	~MineSweeper() {}
	void gameInit();
	void gameLogic();
private:
	class CellState
	{
	public:
		CellState() 
		{
			number = 0;
			mine = false;
			open = false;
			flag = false;
		}
		~CellState() {}
		int number;
		bool mine;
		bool open;
		bool flag;
	};

	CellState** m_board;

	int m_board_width, m_board_height, m_num_mines;
	int m_cursor_row, m_cursor_col;

	void createBoard();
	void updateBoard();
	void openCell(int t_row, int t_col);
	void drawBackground();
	void drawBoard();
};

#endif