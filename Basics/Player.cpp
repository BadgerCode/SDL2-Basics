#include "Player.h"
#include <algorithm>

Player::Player(RenderController* renderController, int startX, int startY, int screenWidth, int screenHeight)
{
	_renderController = renderController;

	_width = 25;
	_height = 75;
	_xPos = startX;
	_yPos = startY;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
}

Player::~Player()
{
}

void Player::Render() const
{
	SDL_Rect r;
	r.x = _xPos;
	r.y = _yPos;
	r.w = _width;
	r.h = _height;

	_renderController->DrawRectangle(&r, 255, 255, 255, 255);
	_renderController->DrawRectangleOutline(&r, 0, 0, 0, 255);
}

void Player::ProcessInput(UserInput userInput)
{
	int speed = 3;
	_xPos = std::min(_screenWidth - _width, std::max(0, _xPos + speed * (userInput.Right - userInput.Left)));
	_yPos = std::min(_screenHeight - _height, std::max(0, _yPos + speed * (userInput.Down - userInput.Up)));
}
