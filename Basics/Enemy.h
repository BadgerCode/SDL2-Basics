#pragma once

#include "RenderController.h"
#include <ctime>
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(RenderController* renderController, RenderableSDLTexture* enemyTexture);
	~Enemy();
	void Render() const override;
	void Update() override;
	std::pair<int, int> GetPosition() const override;
	void SetPosition(int worldX, int worldY) override;
private:
	RenderController* _renderController;
	RenderableSDLTexture* _enemyTexture;
	int _worldX;
	int _worldY;

	clock_t _nextMovementTime;
	int _targetXPos;
	int _targetYPos;

	static clock_t GetNewMovementTime();
	static const int Speed = 3;
	static const int MovementRadius = 250;
};

