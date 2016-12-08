#include "Enemy.h"


Enemy::Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture, int startX, int startY)
{
	_renderController = renderController;
	_enemyTexture = enemyTexture;
	_xPos = startX;
	_yPos = startY;
}

Enemy::~Enemy()
{
}

void Enemy::Render() const
{
	_renderController->RenderTexture(_enemyTexture, _xPos, _yPos);
}
