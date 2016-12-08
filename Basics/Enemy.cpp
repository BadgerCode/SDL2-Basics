#include "Enemy.h"
#include <cstdlib>
#include <algorithm>


Enemy::Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture, int startX, int startY, int screenWidth, int screenHeight)
{
	_renderController = renderController;
	_enemyTexture = enemyTexture;
	_xPos = startX;
	_yPos = startY;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_targetXPos = _xPos;
	_targetYPos = _yPos;
	_nextMovementTime = GetNewMovementTime();
}

Enemy::~Enemy()
{
}

void Enemy::Render() const
{
	_renderController->RenderTexture(_enemyTexture, _xPos, _yPos);
}

void Enemy::Update()
{
	auto atTargetPosition = _xPos == _targetXPos && _yPos == _targetYPos;
	if(atTargetPosition)
	{
		auto nextMovementTimeIsSet = _nextMovementTime != 0;
		if(nextMovementTimeIsSet)
		{
			auto timeToMove = _nextMovementTime <= clock();
			if(timeToMove)
			{
				_nextMovementTime = 0;

				_targetXPos = std::min(_screenWidth - _enemyTexture->TextureRect->w, std::max(0, _xPos + rand() % MovementRadius - MovementRadius/2));
				_targetYPos = std::min(_screenHeight - _enemyTexture->TextureRect->h, std::max(0, _yPos + rand() % MovementRadius - MovementRadius/2));
			}
			else
			{
				// DO NOTHING
			}
		}
		else
		{
			_nextMovementTime = GetNewMovementTime();
		}
	}
	else
	{
		auto xDistance = _xPos - _targetXPos;
		auto yDistance = _yPos - _targetYPos;
		auto distance = sqrt(xDistance*xDistance + yDistance*yDistance);

		if(distance <= Speed)
		{
			_xPos = _targetXPos;
			_yPos = _targetYPos;
		}
		else
		{
			auto ratioOfDistance = static_cast<double>(Speed) / distance;
			_xPos -= ratioOfDistance * xDistance;
			_yPos -= ratioOfDistance * yDistance;
		}
	}
}

clock_t Enemy::GetNewMovementTime()
{
	 return clock() + rand() % 3 * 1000 + 1000;
}
