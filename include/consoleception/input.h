#ifndef INPUT_H
#define INPUT_H

#define INPUTS_LIMIT 8

namespace Input
{
	/**
	 * This function initializes input related settings and should be called
	 * in the start of the main program.
	 */
	void initializeInput();

	/**
	 * This function updates internal variables related to key states and should
	 * be called before using the get functions.
	 */
	void updateInput();

	/**
	 * Checks the state of a given key during last updateInput() call.
	 * @param key Integer representation of desired key, using the constants
	 * defined in curses.h.
	 * @return true if given key was being held during updateInput()
	 * call, false otherwise.
	 */
	bool getKeyHeld(int key);

	/**
	 * Checks if a given key was pressed in last updateInput() call. In this
	 * context, being pressed means that the given key was not being held in
	 * the previous frame, but is being held in the current frame.
	 * NOTE: NOT WORKING PROPERLY YET!
	 * @param key Integer representation of desired key, using the constants
	 * defined in curses.h.
	 * @return true if given key was pressed during updateInput()
	 * call, false otherwise.
	 */
	bool getKeyPressed(int key);

	/**
	 * Checks if a given key was released in last updateInput() call. In this
	 * context, being released means that the given key was being held in
	 * the previous frame, but is not being held in the current frame.
	 * NOTE: NOT WORKING PROPERLY YET!
	 * @param key Integer representation of desired key, using the constants
	 * defined in curses.h.
	 * @return true if given key was released during updateInput()
	 * call, false otherwise.
	 */
	bool getKeyReleased(int key);
}

#endif