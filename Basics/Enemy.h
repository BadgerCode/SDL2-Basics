#pragma once

#include "RenderController.h"

class Enemy
{
public:
	Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture, int startX, int startY);
	~Enemy();

	void Render() const;
private:
	RenderController* _renderController;
	RenderableSDLTexture* _enemyTexture;
	int _xPos;
	int _yPos;
};

