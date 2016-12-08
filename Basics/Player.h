#pragma once

#include "KeyboardController.h"
#include "RenderController.h"

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
	Player(RenderController* render_controller, int startX, int startY, int screenWidth, int screenHeight);
	~Player();

	void Render() const;
	void ProcessInput(UserInput playerMovement);
private:
	RenderController* _renderController;

	SDL_Texture* _playerTexture;
	int _width;
	int _height;
	int _xPos;
	int _yPos;
	int _screenWidth;
	int _screenHeight;
};

