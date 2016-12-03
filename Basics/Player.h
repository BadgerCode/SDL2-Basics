#pragma once

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
	Player(RenderController* render_controller, int startX, int startY);
	~Player();

	void Render() const;
	void ProcessInput(PlayerMovement* playerMovement);
private:
	RenderController* _renderController;
	int _xPos; // TODO: Float
	int _yPos; // TODO: Float
};

