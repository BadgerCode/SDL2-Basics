#include "Enemy.h"
#include "EntityController.h"
#include <cstdlib>


Enemy::Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture): Entity()
{
	_renderController = renderController;
	_enemyTexture = enemyTexture;

	_worldX = 0;
	_worldY = 0;

	_targetXPos = 0;
	_targetYPos = 0;
	_nextMovementTime = GetNewMovementTime();
}

Enemy::~Enemy()
{
}

void Enemy::Render() const
{
	_renderController->RenderWorldTexture(_enemyTexture, _worldX, _worldY);
}

void Enemy::Update()
{
	// TODO: Refactor
	auto atTargetPosition = _worldX == _targetXPos && _worldY == _targetYPos;
	if(atTargetPosition)
	{
		auto nextMovementTimeIsSet = _nextMovementTime != 0;
		if(nextMovementTimeIsSet)
		{
			auto timeToMove = _nextMovementTime <= clock();
			if(timeToMove)
			{
				_nextMovementTime = 0;

				_targetXPos = _worldX + rand() % MovementRadius - MovementRadius/2;
				_targetYPos = _worldY + rand() % MovementRadius - MovementRadius/2;
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
		auto xDistance = _worldX - _targetXPos;
		auto yDistance = _worldY - _targetYPos;
		auto distance = sqrt(xDistance*xDistance + yDistance*yDistance);

		if(distance <= Speed)
		{
			_worldX = _targetXPos;
			_worldY = _targetYPos;
		}
		else
		{
			auto ratioOfDistance = static_cast<double>(Speed) / distance;
			_worldX -= static_cast<int>(ratioOfDistance * xDistance);
			_worldY -= static_cast<int>(ratioOfDistance * yDistance);
		}
	}
}

std::pair<int, int> Enemy::GetPosition() const
{
	return std::pair<int, int>(_worldX, _worldY);
}

void Enemy::SetPosition(int worldX, int worldY)
{
	_worldX = worldX;
	_worldY = worldY;
	_targetXPos = worldX;
	_targetYPos = worldY;
}

clock_t Enemy::GetNewMovementTime()
{
	 return clock() + rand() % 3 * 1000 + 1000;
}
