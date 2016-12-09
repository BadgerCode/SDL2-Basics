#include "KeyboardController.h"



KeyboardController::KeyboardController()
{
	_userInput.Up = false;
	_userInput.Down = false;
	_userInput.Left = false;
	_userInput.Right = false;
}


KeyboardController::~KeyboardController()
{
}

void KeyboardController::ProcessEvent(SDL_Event* event)
{
	auto keyCode = event->key.keysym.sym;
	auto isKeyDown = event->type == SDL_KEYDOWN;

	switch (keyCode)
	{
	case SDLK_d:
		_userInput.Right = isKeyDown;
		break;
	case SDLK_a:
		_userInput.Left = isKeyDown;
		break;
	case SDLK_w:
		_userInput.Up = isKeyDown;
		break;
	case SDLK_s:
		_userInput.Down = isKeyDown;
		break;
	default:
		break;
	}
}

UserInput KeyboardController::GetUserInput() const
{
	return _userInput;
}
