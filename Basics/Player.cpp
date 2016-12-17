#include "Player.h"
#include "LightSource.h"


Player::Player(RenderController* renderController, KeyboardController* keyboardController, 
				RenderableSDLTexture* playerTexture, LightSource* playerLight,
				int startX, int startY, int screenWidth, int screenHeight): Entity()
{
	_renderController = renderController;
	_keyboardController = keyboardController;

	_worldX = startX;
	_worldY = startY;

	_playerTexture = playerTexture;
	_playerLight = playerLight;
	_width = _playerTexture->TextureRect->w;
	_height = _playerTexture->TextureRect->h;

	_screenX = screenWidth / 2;
	_screenY = screenHeight / 2;

	_playerFont = TTF_OpenFont("resources/arial.ttf", 50);
}

Player::~Player()
{
	TTF_CloseFont(_playerFont);
	delete _playerLight;
}

void Player::Render() const
{
	_renderController->RenderWorldTexture(_playerTexture, _worldX - _width / 2, _worldY - _height / 2);
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

	_playerLight->SetWorldPosition(_worldX, _worldY);
}

std::pair<int, int> Player::GetPosition() const
{
	return std::pair<int, int>(_worldX, _worldY);
}