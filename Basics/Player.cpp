#include "Player.h"
#include "SDL2/SDL_image.h"
#include <algorithm>

Player::Player(RenderController* renderController, int startX, int startY, int screenWidth, int screenHeight)
{
	_renderController = renderController;

	_xPos = startX;
	_yPos = startY;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_playerTexture = renderController->LoadTexture("resources/player.png");
	SDL_QueryTexture(_playerTexture, nullptr, nullptr, &_width, &_height);
}

Player::~Player()
{
}

void Player::Render() const
{
	_renderController->RenderTexture(_playerTexture, _xPos, _yPos);
}

void Player::ProcessInput(UserInput userInput)
{
	// TODO: Diagonal speed needs to be fixed (is too fast)
	int speed = 3;
	_xPos = std::min(_screenWidth - _width, std::max(0, _xPos + speed * (userInput.Right - userInput.Left)));
	_yPos = std::min(_screenHeight - _height, std::max(0, _yPos + speed * (userInput.Down - userInput.Up)));
}
