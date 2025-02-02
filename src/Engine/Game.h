#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <list>
#include <string>
#include <SDL.h>

namespace OpenXcom
{

class State;
class Screen;
class Cursor;
class Language;
class SavedGame;
class Mod;
class FpsCounter;

#ifdef __vita__
Uint8 SDL_GetMouseState_Vita(int *x, int *y);
#endif

/**
 * The core of the game engine, manages the game's entire contents and structure.
 * Takes care of encapsulating all the core SDL commands, provides access to all
 * the game's resources and contains a stack state machine to handle all the
 * initializations, events and blits of each state, as well as transitions.
 */
class Game
{
private:
	SDL_Event _event;
	Screen *_screen;
	Cursor *_cursor;
	Language *_lang;
	std::list<State*> _states, _deleted;
	SavedGame *_save;
	Mod *_mod;
	bool _quit, _init;
	FpsCounter *_fpsCounter;
	bool _mouseActive;
	unsigned int _timeOfLastFrame;
	int _timeUntilNextFrame;
	static const double VOLUME_GRADIENT;

#ifdef __vita__
	void HandleControllerAxisEvent(const SDL_JoyAxisEvent &motion);
	void HandleControllerButtonEvent(const SDL_JoyButtonEvent &button);
	void ProcessControllerAxisMotion();
	void ActivateAction(SDL_Event ev);

	enum
	{
		CONTROLLER_L_DEADZONE = 3000,
		CONTROLLER_R_DEADZONE = 25000
	};

	// used to convert user-friendly pointer speed values into more useable ones
	const double CONTROLLER_SPEED_MOD = 2000000.0;
	double controllerPointerSpeed = 10.0 / CONTROLLER_SPEED_MOD;

	// bigger value correndsponds to faster pointer movement speed with bigger stick axis values
	const double CONTROLLER_AXIS_SPEEDUP = 1.03;

	SDL_Joystick *gameController = nullptr;
	int16_t controllerLeftXAxis = 0;
	int16_t controllerLeftYAxis = 0;
	int16_t controllerRightXAxis = 0;
	int16_t controllerRightYAxis = 0;
	uint32_t lastControllerTime = 0;
	bool leftScrollActive = false;
	bool rightScrollActive = false;
	bool upScrollActive = false;
	bool downScrollActive = false;
	bool lShoulderPressed = false;
	bool rShoulderPressed = false;
	bool ctrlMod = false;
#endif

public:
	/// Creates a new game and initializes SDL.
	Game(const std::string &title);
	/// Cleans up all the game's resources and shuts down SDL.
	~Game();
	/// Starts the game's state machine.
	void run();
	/// Quits the game.
	void quit();
	/// Sets the game's audio volume.
	void setVolume(int sound, int music, int ui);
	/// Adjusts a linear volume level to an exponential one.
	static double volumeExponent(int volume);
	/// Gets the game's display screen.
	Screen *getScreen() const;
	/// Gets the game's cursor.
	Cursor *getCursor() const;
	/// Gets the FpsCounter.
	FpsCounter *getFpsCounter() const;
	/// Resets the state stack to a new state.
	void setState(State *state);
	/// Pushes a new state into the state stack.
	void pushState(State *state);
	/// Pops the last state from the state stack.
	void popState();
	/// Gets the currently loaded language.
	Language *getLanguage() const;
	/// Gets the currently loaded saved game.
	SavedGame *getSavedGame() const;
	/// Sets a new saved game for the game.
	void setSavedGame(SavedGame *save);
	/// Gets the currently loaded mod.
	Mod *getMod() const;
	/// Loads the mods specified in the game options.
	void loadMods();
	/// Sets whether the mouse cursor is activated.
	void setMouseActive(bool active);
	/// Returns whether current state is the param state
	bool isState(State *state) const;
	/// Returns whether the game is shutting down.
	bool isQuitting() const;
	/// Loads the default and current language.
	void loadLanguages();
	/// Sets up the audio.
	void initAudio();
};

}
