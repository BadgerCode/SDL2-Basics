#pragma once

#include "SDL2/SDL_ttf.h"
#include "KeyboardController.h"
#include "RenderController.h"
#include "RenderableSDLTexture.h"
#include "Entity.h"
#include "LightSource.h"

struct PlayerMovement
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

class Player : public Entity
{
public:
	Player(RenderController* renderController, KeyboardController* keyboardController, 
			RenderableSDLTexture* playerTexture, LightSource* playerLight,
			int startX, int startY, int screenWidth, int screenHeight);
	~Player();

	void Render() const override;
	void Update() override;
	std::pair<int, int> GetPosition() const override;
private:
	RenderController* _renderController;
	KeyboardController* _keyboardController;

	RenderableSDLTexture* _playerTexture;
	LightSource* _playerLight;

	int _width;
	int _height;
	int _worldX;
	int _worldY;
	int _screenX;
	int _screenY;

	TTF_Font* _playerFont;
};

