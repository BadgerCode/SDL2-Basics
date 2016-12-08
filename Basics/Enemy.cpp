#include "Enemy.h"


Enemy::Enemy(RenderController* renderController, int startX, int startY)
{
	_renderController = renderController;
	_xPos = startX;
	_yPos = startY;
}

Enemy::~Enemy()
{
}

void Enemy::Render() const
{
	SDL_Rect enemyRect;
	enemyRect.x = _xPos;
	enemyRect.y = _yPos;
	enemyRect.w = 20;
	enemyRect.h = 20;

	_renderController->DrawRectangle(&enemyRect, 255, 0, 0, 255);
}
