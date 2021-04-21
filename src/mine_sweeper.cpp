#include "consoleception/mine_sweeper.h"

MineSweeper::MineSweeper(int t_width, int t_height, int t_num_mines):
	GameBase(30, 2*t_width + 1, 2*t_height + 1)
{
	m_board_width = t_width;
	m_board_height = t_height;
	m_num_mines = t_num_mines;
}

void MineSweeper::gameInit()
{
	createBoard();
	drawBackground();
	drawBoard();
}

void MineSweeper::gameLogic()
{
	updateBoard();
	drawBoard();
}

void MineSweeper::createBoard()
{
	// Initializing board in memory

	m_board = new CellState*[m_board_height];
	for (int i = 0; i < m_board_height; ++i)
	{
		m_board[i] = new CellState[m_board_width];
	}

	m_cursor_row = m_cursor_col = 0;

	// Generating mines

	srand(time(NULL));

	for (int i = 0; i < m_num_mines; ++i)
	{
		int mine_x = rand() % m_board_width;
		int mine_y = rand() % m_board_height;
		m_board[mine_y][mine_x].mine = true;
	}

	// Calculate cell numbers

	for (int i = 0; i < m_board_height; ++i)
	{
		for (int j = 0; j < m_board_width; ++j)
		{
			// If current cell has a mine, skip iteration
			if (m_board[i][j].mine)
			{
				continue;
			}

			// Count adjacent mines
			for (int k = i - 1; k < i + 2; ++k)
			{
				for (int l = j - 1; l < j + 2; ++l)
				{
					// Skip iteraction if [k][l] is out of range
					if (k < 0 || l < 0 || k >= m_board_height || l >= m_board_width)
					{
						continue;
					}
					if (m_board[k][l].mine)
					{
						m_board[i][j].number++;
					}
				}
			}
		}
	}
}

void MineSweeper::updateBoard()
{
	if (Input::getKeyHeld(KEY_LEFT) && m_cursor_col > 0)
	{
		m_cursor_col--;
	}
	if (Input::getKeyHeld(KEY_UP) && m_cursor_row > 0)
	{
		m_cursor_row--;
	}
	if (Input::getKeyHeld(KEY_RIGHT) && m_cursor_col < m_board_width - 1)
	{
		m_cursor_col++;
	}
	if (Input::getKeyHeld(KEY_DOWN) && m_cursor_row < m_board_height - 1)
	{
		m_cursor_row++;
	}
	if (Input::getKeyHeld('a'))
	{
		openCell(m_cursor_row, m_cursor_col);
	}
}

void MineSweeper::openCell(int t_row, int t_col)
{
	if (m_board[t_row][t_col].open)
	{
		return;
	}

	m_board[t_row][t_col].open = true;

	if (m_board[t_row][t_col].number == 0 && !m_board[t_row][t_col].mine)
	{
		// Open adjacent cells
		for (int i = t_row - 1; i < t_row + 2; i++)
		{
			for (int j = t_col - 1; j < t_col + 2; j++)
			{
				if (i < 0 || j < 0 || i >= m_board_height || j >= m_board_width)
				{
					continue;
				}
				openCell(i, j);
			}
		}
	}
}

void MineSweeper::drawBackground()
{
	for (int j = 0; j < m_board_width; ++j)
	{
		Video::setSinglePixel('-', 0, 0, 2*j + 1);
		Video::setSinglePixel('+', 0, 0, 2*j + 2);
	}
	Video::setSinglePixel('+', 0, 0, 0);
	for (int i = 0; i < m_board_height; ++i)
	{
		for (int j = 0; j < m_board_width; ++j)
		{
			Video::setSinglePixel('-', 0, 2*i + 2, 2*j + 1);
			Video::setSinglePixel('+', 0, 2*i + 2, 2*j + 2);
			Video::setSinglePixel('|', 0, 2*i + 1, 2*j + 2);
		}
		Video::setSinglePixel('+', 0, 2*i + 2, 0);
		Video::setSinglePixel('|', 0, 2*i + 1, 0);
	}
}

void MineSweeper::drawBoard()
{
	for (int i = 0; i < m_board_height; ++i)
	{
		for (int j = 0; j < m_board_width; ++j)
		{
			char cell = (m_board[i][j].open ? m_board[i][j].number + '0' : ' ');
			attr_t attrib = (i == m_cursor_row && j == m_cursor_col ? A_STANDOUT : 0);
			if (m_board[i][j].open && m_board[i][j].mine)
			{
				cell = '*';
				attrib |= COLOR_PAIR(1);
			}
			Video::setSinglePixel(cell, attrib, 2*i + 1, 2*j + 1);
		}
	}
}