#pragma once

#include "RenderController.h"
#include <ctime>
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(RenderController* renderController, EntityController* entityController, RenderableSDLTexture* enemyTexture, int startX, int startY, int screenWidth, int screenHeight);
	~Enemy();
	void Render() const override;
	void Update() override;
	std::pair<int, int> GetPosition() const override;
	clock_t GetLastSpawnTime() const;
private:
	RenderController* _renderController;
	RenderableSDLTexture* _enemyTexture;
	int _xPos;
	int _yPos;
	int _screenWidth;
	int _screenHeight;

	clock_t _nextMovementTime;
	int _targetXPos;
	int _targetYPos;

	static clock_t GetNewMovementTime();
	static const int Speed = 3;
	static const int MovementRadius = 250;

	clock_t _lastSpawnTime;
};

