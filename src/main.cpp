#include <curses.h>
#include <time.h>
#include <string.h>

#include "consoleception/test_game.h"
#include "consoleception/game_base.h"
#include "consoleception/mine_sweeper.h"
#include "consoleception/input.h"

int main(int argc, char* argv[])
{
    // Initializations

    GameBase* game = new MineSweeper(40, 10, 60);
    // GameBase* game = new TestGame();

    game->gameInit();

    // Loop

    for (;;)
    {
        game->gameLoop();
    }

    endwin();

    return 0;
}