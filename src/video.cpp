#include "consoleception/video.h"

namespace Video
{
	Pixel** screen;
	int m_rows, m_cols, m_max_rows, m_max_cols;
	int cursor_x = 0;
	int cursor_y = 0;
	attr_t last_attribute = 0;
	WINDOW* game;

	void initializeVideo(int t_rows, int t_cols)
	{
		m_rows = t_rows;
		m_cols = t_cols;

		initscr(); // ncurses init
	    curs_set(0); // setting cursor invisible
	    cbreak();
	    start_color();
	    init_pair(1, COLOR_RED, COLOR_BLACK);

	    //signal(SIGWINCH, resizeHandler);

	    updateMaxSize();
	    game = newwin(m_rows + 2, m_cols + 2, (m_max_rows - m_rows) / 2 - 1, (m_max_cols - m_cols) / 2 - 1);

	    box(game, 0, 0);
	    //wborder(game, 0, 0, 0, 0, 0, 0, 0, 0);

		//printw("initalizing");

	    screen = new Pixel*[m_rows];
	    for (int i = 0; i < m_rows; ++i)
	    {
	    	screen[i] = new Pixel[m_cols];
	    }
	}

	// void* resizeHandler(int sig)
	// {
	// 	int nh, nw;
	// 	getmaxyx(stdscr, nh, nw);
	// 	mvwin(game, (nh - m_height) / 2 - 1, (nw - m_width) / 2 - 1);
	// }

	void updateMaxSize()
	{
	    getmaxyx(stdscr, m_max_rows, m_max_cols);
	}

	void setSinglePixel(char t_content, attr_t t_attributes, int t_row, int t_col)
	{
		screen[t_row][t_col].content = t_content;
		screen[t_row][t_col].attributes = t_attributes;
	}

	void setStringPixel(char* t_content, int t_size, attr_t t_attributes, int t_row, int t_col)
	{
		for (int i = 0; i < t_size; ++i)
		{
			screen[t_row][t_col + i].content = t_content[i];
			screen[t_row][t_col + i].attributes = t_attributes;
		}
	}

	void refreshScreen()
	{
		//printw("refreshing");

		updateMaxSize();

		int new_row = m_max_rows > m_rows ? (m_max_rows - m_rows) / 2 - 1 : 0;
		int new_col = m_max_cols > m_cols ? (m_max_cols - m_cols) / 2 - 1 : 0;

		mvwin(game, new_row, new_col);

		for (int i = 0; i < m_rows; ++i)
		{
			wmove(game, i + 1, 1);
			for (int j = 0; j < m_cols; ++j)
			{
				if (screen[i][j].content == '\0')
				{
					wmove(game, i + 1, j + 2);
					continue;
				}
				wattroff(game, last_attribute);
				wattron(game, screen[i][j].attributes);
				last_attribute = screen[i][j].attributes;
				waddch(game, screen[i][j].content);
			}
		}

		wrefresh(game);
	}
}