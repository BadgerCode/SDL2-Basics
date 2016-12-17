#include "Player.h"


Player::Player(RenderController* renderController, KeyboardController* keyboardController, 
				RenderableSDLTexture* playerTexture, int startX, int startY, int screenWidth, 
				int screenHeight): Entity()
{
	_renderController = renderController;
	_keyboardController = keyboardController;

	_worldX = startX;
	_worldY = startY;

	_playerTexture = playerTexture;
	_width = _playerTexture->TextureRect->w;
	_height = _playerTexture->TextureRect->h;

	_screenX = screenWidth / 2;
	_screenY = screenHeight / 2;

	_playerFont = TTF_OpenFont("resources/arial.ttf", 50);
}

Player::~Player()
{
	TTF_CloseFont(_playerFont);
}

void Player::Render() const
{
	_renderController->RenderScreenTexture(_playerTexture, _screenX - _height / 2, _screenY - _width / 2);

	char buffer[100];
	sprintf_s(buffer, "(%d, %d)", _worldX, _worldY);
	SDL_Color fontColor = { 0, 0, 0, 255 };
	_renderController->RenderScreenText(_playerFont, buffer, fontColor, 200, 200);
}

void Player::Update()
{
	auto userInput = _keyboardController->GetUserInput();

	// TODO: Diagonal speed needs to be fixed (is too fast)
	int speed = 3;
//	_worldX = std::min(_screenWidth - _width, std::max(0, _worldX + speed * (userInput.Right - userInput.Left)));
//	_worldY = std::min(_screenHeight - _height, std::max(0, _worldY + speed * (userInput.Down - userInput.Up)));
	_worldX = _worldX + speed * (userInput.Right - userInput.Left);
	_worldY = _worldY + speed * (userInput.Down - userInput.Up);
}

std::pair<int, int> Player::GetPosition() const
{
	return std::pair<int, int>(_worldX, _worldY);
}

std::pair<int, int> Player::GetSize() const
{
	return std::pair<int, int>(_width, _height);
}
