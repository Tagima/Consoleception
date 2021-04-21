#ifndef TEST_GAME_H
#define TEST_GAME_H

#include "consoleception/game_base.h"
#include <string.h>

class TestGame : public GameBase
{
public:
	TestGame() : GameBase(10, 50, 30) {}
	~TestGame() {}
	void gameInit();
	void gameLogic();
};

#endif