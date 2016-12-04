#pragma once

#include "SDL2/SDL.h"

struct UserInput
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

class KeyboardController
{
public:
	KeyboardController();
	~KeyboardController();

	void ProcessEvent(SDL_Event* event);
	UserInput GetUserInput() const;
private:
	UserInput _userInput;
};

