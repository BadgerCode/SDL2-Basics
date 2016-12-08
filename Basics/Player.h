#pragma once

#include "KeyboardController.h"
#include "RenderController.h"
#include "SDLTexture.h"

struct PlayerMovement
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

class Player
{
public:
	Player(RenderController* render_controller, SDLTexture* playerTexture, int startX, int startY, int screenWidth, int screenHeight);
	~Player();

	void Render() const;
	void ProcessInput(UserInput playerMovement);
private:
	RenderController* _renderController;

	SDLTexture* _playerTexture;
	int _width;
	int _height;
	int _xPos;
	int _yPos;
	int _screenWidth;
	int _screenHeight;
};

