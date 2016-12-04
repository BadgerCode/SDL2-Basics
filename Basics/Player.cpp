#include "Player.h"

Player::Player(RenderController* renderController, int startX, int startY)
{
	_renderController = renderController;
	_xPos = startX;
	_yPos = startY;
}

Player::~Player()
{
}

void Player::Render() const
{
	SDL_Rect r;
	r.x = _xPos;
	r.y = _yPos;
	r.w = 25;
	r.h = 75;

	_renderController->DrawRectangle(&r, 255, 255, 255, 255);
	_renderController->DrawRectangleOutline(&r, 0, 0, 0, 255);
}

void Player::ProcessInput(UserInput userInput)
{
	int speed = 3;
	_xPos += speed * (userInput.Right - userInput.Left);
	_yPos += speed * (userInput.Down - userInput.Up);
}