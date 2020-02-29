#include <curses.h>
#include <time.h>
#include <string.h>

#include "consoleception/input.h"

void m_sleep(int num_cycles)
{
    int last_clock = num_cycles + clock();
    while(clock() < last_clock);
    return;
}

int main(int argc, char* argv[])
{
    // INITIALIZATIONS

    int max_row, max_col;

    int framerate = 10;

    initscr(); // ncurses init

    getmaxyx(stdscr, max_row, max_col);

    curs_set(0); // setting cursor invisible

    Input::initializeInput();

    cbreak(); // I don't know

    char messages[5][41] = {
        "****************************************",
        "INPUT DRIVER TEST",
        "Press arrow keys and see if",
        "they show up in the array below.",
        "****************************************"
    };

    int arrayInputs[4] = {KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT};
    char arrayInputsText[4][10] = {"KEY_LEFT", "KEY_UP", "KEY_DOWN", "KEY_RIGHT"};

    int position = 0;

    int arbitraryCounter = 0;

    // PRINTING "BACKGROUND"

    for (int i = 0; i < 5; ++i)
    {
        mvprintw(i, (max_col - strlen(messages[i]))/2, "%s", messages[i]);
    }

    // LOOP

    for (;;)
    {
        // GETTING START TIME

        clock_t start = clock();

        // PRINTING DATA FROM INPUT

        Input::updateInput();

        mvprintw(7, 2, "Keys held in current frame:     ");
        for (int i = 0; i < 4; ++i)
        {
            if (Input::getKeyHeld(arrayInputs[i]))
            {
                printw("%s ", arrayInputsText[i]);
            }
        }
        printw("                              ");

        mvprintw(8, 2, "Keys pressed in current frame:  ");
        for (int i = 0; i < 4; ++i)
        {
            if (Input::getKeyPressed(arrayInputs[i]))
            {
                printw("%s ", arrayInputsText[i]);
            }
        }
        printw("                              ");

        mvprintw(9, 2, "Keys released in current frame: ");
        for (int i = 0; i < 4; ++i)
        {
            if (Input::getKeyReleased(arrayInputs[i]))
            {
                printw("%s ", arrayInputsText[i]);
            }
        }
        printw("                              ");

        refresh();

        // SLEEP

        clock_t end = clock();

        int cycles_delta = end - start;
        int cycles_to_wait = (cycles_delta < CLOCKS_PER_SEC/framerate ? CLOCKS_PER_SEC/framerate - cycles_delta : 0);

        m_sleep(cycles_to_wait);

    }

    endwin();

    return 0;
}