#ifndef VIDEO_H
#define VIDEO_H

#include <curses.h>

namespace Video
{
	class Pixel
	{
	public:
		Pixel() {content = '\0';}
		~Pixel() {}
		char content;
		attr_t attributes;
	};

	void initializeVideo(int t_rows, int t_cols);
	//void* resizeHandler(int sig);
	void refreshScreen();
	void updateMaxSize();
	void setSinglePixel(char t_content, attr_t t_attributes, int t_row, int t_col);
	void setStringPixel(char* t_content, int t_size, attr_t t_attributes, int t_row, int t_col);

	extern Pixel** screen;
	extern int m_width, m_height, m_max_width, m_max_height;
	extern int cursor_x, cursor_y; // TODO: not implemented yet
	extern attr_t last_attribute;
	extern WINDOW* game;
}

#endif