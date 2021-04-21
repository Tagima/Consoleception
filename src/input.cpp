#include "consoleception/input.h"

namespace Input
{
	std::vector<int> m_prsdKeys;
	std::vector<int> m_lastKeys;
	std::vector<int> m_heldKeys;
	std::vector<int> m_rlsdKeys;

	void initializeInput()
	{
		// Initializing ncurses settings

		nonl();
		noecho(); // Avoid printing the typed character on screen
		nodelay(stdscr, TRUE); // Make the program not freeze when getch() is called
		keypad(stdscr, TRUE); // Include special characters in getch() queue
	}

	void updateInput()
	{
		// Updating last keys vector

		m_lastKeys = m_heldKeys;

		// Updating held keys vector

		m_heldKeys.clear();

		for (char i = 0; i < INPUTS_LIMIT; ++i)
		{
			int key = getch();
			if (key == ERR)
			{
				break;
			}
			m_heldKeys.push_back(key);
		}

		flushinp(); // Avoid that inputs in queue get read in next frame

		// Updating released keys vector

		m_rlsdKeys.clear();

		for (char i = 0; i < m_lastKeys.size(); ++i)
		{
			// Check if current lastKey does not exist in heldKeys vector
			std::vector<int>::iterator it = find(
				m_heldKeys.begin(), m_heldKeys.end(), m_lastKeys[i]);
			if (it == m_heldKeys.end())
			{
				m_rlsdKeys.push_back(m_lastKeys[i]);
			}
		}

		// Updating pressed keys vector

		m_prsdKeys.clear();

		for (char i = 0; i < m_heldKeys.size(); ++i)
		{
			// Check if current heldKey does not exist in lastKeys vector
			std::vector<int>::iterator it = find(
				m_lastKeys.begin(), m_lastKeys.end(), m_heldKeys[i]);
			if (it == m_lastKeys.end())
			{
				m_prsdKeys.push_back(m_heldKeys[i]);
			}
		}
	}

	bool getKeyHeld(int key)
	{
		// Check if given key exists in m_heldKeys

		std::vector<int>::iterator it = find(
			m_heldKeys.begin(), m_heldKeys.end(), key);

		return (it != m_heldKeys.end());
	}

	bool getKeyPressed(int key)
	{
		// Check if given key exists in m_prsdKeys

		std::vector<int>::iterator it = find(
			m_prsdKeys.begin(), m_prsdKeys.end(), key);

		return (it != m_prsdKeys.end());
	}

	bool getKeyReleased(int key)
	{
		// Check if given key exists in m_rlsdKeys

		std::vector<int>::iterator it = find(
			m_rlsdKeys.begin(), m_rlsdKeys.end(), key);

		return (it != m_rlsdKeys.end());
	}
}