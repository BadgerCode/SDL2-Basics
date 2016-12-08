#pragma once

#include "RenderController.h"

class Enemy
{
public:
	Enemy(RenderController* renderController, int startX, int startY);
	~Enemy();

	void Render() const;
private:
	RenderController* _renderController;
	int _xPos;
	int _yPos;
};

