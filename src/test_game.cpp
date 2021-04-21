#include "consoleception/test_game.h"

void TestGame::gameInit()
{
	char messages[5][41] = {
		"****************************************",
		"INPUT DRIVER TEST",
		"Press arrow keys and see if",
		"they show up in the array below.",
		"****************************************"
	};

	for (int i = 0; i < 5; ++i)
    {
    	Video::setStringPixel(messages[i], strlen(messages[i]), 0, i, (50 - strlen(messages[i])) / 2);
        //mvprintw(i, (max_col - strlen(messages[i]))/2, "%s", messages[i]);
    }

    //printf("gameinit");
}

void TestGame::gameLogic()
{
	int arrayInputs[4] = {KEY_LEFT, KEY_UP, KEY_DOWN, KEY_RIGHT};
	char arrayInputsText[4][10] = {"KEY_LEFT", "KEY_UP", "KEY_DOWN", "KEY_RIGHT"};

	Video::setStringPixel("Keys held in current frame:     ", 33, 0, 7, 2);
	//mvprintw(7, 2, "Keys held in current frame:     ");

	//std::string text = "";
	for (int i = 0; i < 4; ++i)
	{
		if (Input::getKeyHeld(arrayInputs[i]))
		{
			Video::setStringPixel(arrayInputsText[i], strlen(arrayInputsText[i]), A_STANDOUT | COLOR_PAIR(1), 7, 36);
			//printw("%s ", arrayInputsText[i]);
		}
	}
	//printw("                              ");

	Video::setStringPixel("Keys pressed in current frame:  ", 33, 0, 8, 2);
	//mvprintw(8, 2, "Keys pressed in current frame:  ");
	for (int i = 0; i < 4; ++i)
	{
		if (Input::getKeyPressed(arrayInputs[i]))
		{
			Video::setStringPixel(arrayInputsText[i], strlen(arrayInputsText[i]), A_BLINK | COLOR_PAIR(1), 8, 36);
			//printw("%s ", arrayInputsText[i]);
		}
	}
	//printw("                              ");

	Video::setStringPixel("Keys released in current frame: ", 33, 0, 9, 2);
	//mvprintw(9, 2, "Keys released in current frame: ");
	for (int i = 0; i < 4; ++i)
	{
		if (Input::getKeyReleased(arrayInputs[i]))
		{
			Video::setStringPixel(arrayInputsText[i], strlen(arrayInputsText[i]), A_BOLD | COLOR_PAIR(1), 9, 36);
			//printw("%s ", arrayInputsText[i]);
		}
	}
	//printw("                              ");

	Video::setSinglePixel(ACS_ULCORNER, 0, 11, 2);
	Video::setSinglePixel(ACS_URCORNER, 0, 11, 3);
	Video::setSinglePixel(ACS_UARROW, 0, 11, 4);
	Video::setSinglePixel(ACS_VLINE, 0, 11, 5);
	Video::setSinglePixel(ACS_TTEE, 0, 11, 6);
	Video::setSinglePixel(ACS_S1, 0, 11, 7);
	Video::setSinglePixel(ACS_RTEE, 0, 11, 8);
	Video::setSinglePixel(ACS_LANTERN, 0, 11, 9);
	Video::setSinglePixel(ACS_HLINE, 0, 11, 10);
}