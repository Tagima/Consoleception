#include "consoleception/game_base.h"

GameBase::GameBase(int t_frameRate = 30, int t_cols = 50, int t_rows = 20) : m_frameRate(t_frameRate) 
{
	Video::initializeVideo(t_rows, t_cols);
	Input::initializeInput();
	gameInit();
}

void GameBase::gameLoop()
{
	clock_t start = clock();
	Input::updateInput();
	gameLogic();
	Video::refreshScreen();
	clock_t end = clock();
	clock_t cycles_delta = end - start;
    clock_t cycles_to_wait = (cycles_delta < CLOCKS_PER_SEC/m_frameRate ?
    	CLOCKS_PER_SEC/m_frameRate - cycles_delta : 0);
    gameSleep(cycles_to_wait);
}

void GameBase::gameSleep(clock_t cycles)
{
	clock_t last_clock = cycles + clock();
    while(clock() < last_clock);
}