#include "Player.h"
#include <algorithm>


Player::Player(RenderController* renderController, KeyboardController* keyboardController, 
				RenderableSDLTexture* playerTexture, int startX, int startY, int screenWidth, 
				int screenHeight)
{
	_renderController = renderController;
	_keyboardController = keyboardController;

	_xPos = startX;
	_yPos = startY;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_playerTexture = playerTexture;
	_width = _playerTexture->TextureRect->w;
	_height = _playerTexture->TextureRect->h;
}

Player::~Player()
{
}

void Player::Render() const
{
	_renderController->RenderTexture(_playerTexture, _xPos, _yPos);
}

void Player::Update()
{
	auto userInput = _keyboardController->GetUserInput();

	// TODO: Diagonal speed needs to be fixed (is too fast)
	int speed = 3;
	_xPos = std::min(_screenWidth - _width, std::max(0, _xPos + speed * (userInput.Right - userInput.Left)));
	_yPos = std::min(_screenHeight - _height, std::max(0, _yPos + speed * (userInput.Down - userInput.Up)));
}
