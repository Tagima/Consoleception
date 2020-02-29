#include <curses.h>

#include "consoleception/input.h"

namespace Input
{
	int* _prsdKeys;
	int* _lastKeys;
	int* _heldKeys;
	int* _rlsdKeys;
	char _prsdKeysSize;
	char _lastKeysSize;
	char _heldKeysSize;
	char _rlsdKeysSize;

	void initializeInput()
	{
		// Initializing ncurses settings

		noecho(); // Avoid printing the typed character on screen
		nodelay(stdscr, TRUE); // Make the program not freeze when getch() is called
		keypad(stdscr, TRUE); // Include special characters in getch() queue

		_prsdKeys = new int[INPUTS_LIMIT];
		_lastKeys = new int[INPUTS_LIMIT];
		_heldKeys = new int[INPUTS_LIMIT];
		_rlsdKeys = new int[INPUTS_LIMIT];

		_prsdKeysSize = _lastKeysSize = _heldKeysSize = _rlsdKeysSize = 0;
	}

	void updateInput()
	{
		// Updating last keys array

		for (char i = 0; i < _heldKeysSize; ++i)
		{
			_lastKeys[i] = _heldKeys[i];
		}
		_lastKeysSize = _heldKeysSize;

		// Updating held keys array

		for (char i = 0; i < INPUTS_LIMIT; ++i)
		{
			int key = getch();
			if (key == ERR)
			{
				_heldKeysSize = i;
				break;
			}
			_heldKeys[i] = key;
		}

		flushinp(); // Avoid that inputs in queue get read in next frame

		// Updating released keys array

		_rlsdKeysSize = 0;

		for (char i = 0; i < _lastKeysSize; ++i)
		{
			bool released = true;
			for (char j = 0; j < _heldKeysSize; ++j)
			{
				if (_lastKeys[i] == _heldKeys[j])
				{
					released = false;
					break;
				}
			}
			if (released == true)
			{
				_rlsdKeys[_rlsdKeysSize++] = _lastKeys[i];
			}
		}

		// Updating pressed keys array

		_prsdKeysSize = 0;

		for (char i = 0; i < _heldKeysSize; ++i)
		{
			bool pressed = true;
			for (char j = 0; j < _lastKeysSize; ++j)
			{
				if (_heldKeys[i] == _lastKeys[j])
				{
					pressed = false;
					break;
				}
			}
			if (pressed == true)
			{
				_prsdKeys[_prsdKeysSize++] = _heldKeys[i];
			}
		}
	}

	bool getKeyHeld(int key)
	{
		// Check if given key exists in _heldKeys

		for (char i = 0; i < _heldKeysSize; ++i)
		{
			if (_heldKeys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	bool getKeyPressed(int key)
	{
		// Check if given key exists in _prsdKeys

		for (char i = 0; i < _prsdKeysSize; ++i)
		{
			if (_prsdKeys[i] == key)
			{
				return true;
			}
		}
		return false;
	}

	bool getKeyReleased(int key)
	{
		// Check if given key exists in _rlsdKeys

		for (char i = 0; i < _rlsdKeysSize; ++i)
		{
			if (_rlsdKeys[i] == key)
			{
				return true;
			}
		}
		return false;
	}
}