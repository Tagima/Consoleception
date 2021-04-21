#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "consoleception/input.h"
#include "consoleception/video.h"
#include <ctime>

class GameBase
{
public:
	GameBase(int t_frameRate, int t_cols, int t_rows);
	~GameBase() {}
	void gameLoop();
	virtual void gameLogic() {}
	virtual void gameInit() {}
	
protected:
	int m_frameRate;
	void gameSleep(clock_t cycles);
};

#endif