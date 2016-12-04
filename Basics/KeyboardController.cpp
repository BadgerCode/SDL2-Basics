#include "KeyboardController.h"



KeyboardController::KeyboardController()
{
}


KeyboardController::~KeyboardController()
{
}

void KeyboardController::ProcessEvent(SDL_Event* event)
{
	bool keyPressed = event->type == SDL_KEYDOWN;
	auto keyCode = event->key.keysym.sym;

	switch (keyCode)
	{
	case SDLK_d:
		_userInput.Right = keyPressed;
		break;
	case SDLK_a:
		_userInput.Left = keyPressed;
		break;
	case SDLK_w:
		_userInput.Up = keyPressed;
		break;
	case SDLK_s:
		_userInput.Down = keyPressed;
		break;
	default:
		break;
	}
}

UserInput KeyboardController::GetUserInput() const
{
	return _userInput;
}
