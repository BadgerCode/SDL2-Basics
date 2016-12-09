#include "Enemy.h"
#include "EntityController.h"
#include <cstdlib>
#include <algorithm>


Enemy::Enemy(RenderController* renderController, EntityController* entityController, 
			RenderableSDLTexture* enemyTexture, int startX, int startY, int screenWidth, int screenHeight): Entity(entityController)
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

	_lastSpawnTime = clock() + 4000;
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
	if (clock() > _lastSpawnTime + 1000) {
		_lastSpawnTime = clock();

		auto closeEntities = _entityController->FindInRange(_xPos + _enemyTexture->TextureRect->w / 2, _yPos + _enemyTexture->TextureRect->h / 2, 100);
		for (auto entity : closeEntities)
		{
			auto enemy = dynamic_cast<Enemy*>(entity);
			if(entity == this || enemy == nullptr || enemy->GetLastSpawnTime() + 1000 < clock())
			{
				continue;
			}

			auto entityPosition = entity->GetPosition();
			auto spawn_x = _xPos + (entityPosition.first - _xPos) / 2;
			auto spawn_y = _yPos + (entityPosition.second - _yPos) / 2;
			_entityController->AddEnemy(spawn_x, spawn_y);
		}
	}

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
			_xPos -= static_cast<int>(ratioOfDistance * xDistance);
			_yPos -= static_cast<int>(ratioOfDistance * yDistance);
		}
	}
}

std::pair<int, int> Enemy::GetPosition() const
{
	return std::pair<int, int>(_xPos, _yPos);
}

clock_t Enemy::GetLastSpawnTime() const
{
	return _lastSpawnTime;
}

clock_t Enemy::GetNewMovementTime()
{
	 return clock() + rand() % 3 * 1000 + 1000;
}
