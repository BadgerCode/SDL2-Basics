#include "Enemy.h"
#include "EntityController.h"
#include <cstdlib>


Enemy::Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture, 
			int startX, int startY): Entity()
{
	_renderController = renderController;
	_enemyTexture = enemyTexture;
	_xPos = startX;
	_yPos = startY;

	_targetXPos = _xPos;
	_targetYPos = _yPos;
	_nextMovementTime = GetNewMovementTime();
}

Enemy::~Enemy()
{
}

void Enemy::Render() const
{
	_renderController->RenderWorldTexture(_enemyTexture, _xPos, _yPos);
}

void Enemy::Update()
{
	// TODO: Refactor
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

				_targetXPos = _xPos + rand() % MovementRadius - MovementRadius/2;
				_targetYPos = _yPos + rand() % MovementRadius - MovementRadius/2;
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
			_xPos -= static_cast<int>(ratioOfDistance * xDistance);
			_yPos -= static_cast<int>(ratioOfDistance * yDistance);
		}
	}
}

std::pair<int, int> Enemy::GetPosition() const
{
	return std::pair<int, int>(_xPos, _yPos);
}

clock_t Enemy::GetNewMovementTime()
{
	 return clock() + rand() % 3 * 1000 + 1000;
}
