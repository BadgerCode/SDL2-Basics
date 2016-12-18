#include "Player.h"
#include "LightSource.h"


Player::Player(RenderController* renderController, KeyboardController* keyboardController, 
				RenderableSDLTexture* playerTexture, LightSource* playerLight): Entity()
{
	_renderController = renderController;
	_keyboardController = keyboardController;

	_worldX = 0;
	_worldY = 0;

	_playerTexture = playerTexture;
	_playerLight = playerLight;
	_width = _playerTexture->TextureRect->w;
	_height = _playerTexture->TextureRect->h;
}

Player::~Player()
{
	delete _playerLight;
}

void Player::Render() const
{
	_renderController->RenderWorldTexture(_playerTexture, _worldX, _worldY);
}

void Player::Update()
{
	auto userInput = _keyboardController->GetUserInput();

	// TODO: Diagonal speed needs to be fixed (is too fast)
	int speed = 3;
	_worldX = _worldX + speed * (userInput.Right - userInput.Left);
	_worldY = _worldY + speed * (userInput.Down - userInput.Up);

	_playerLight->_worldX = _worldX;
	_playerLight->_worldY = _worldY;
}

std::pair<int, int> Player::GetPosition() const
{
	return std::pair<int, int>(_worldX, _worldY);
}

void Player::SetPosition(int worldX, int worldY)
{
	_worldX = worldX;
	_worldY = worldY;
}
