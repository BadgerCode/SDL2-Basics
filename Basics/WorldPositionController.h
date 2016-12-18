#pragma once
#include <utility>
#include "Entity.h"

class WorldPositionController
{
public:
	WorldPositionController(int screenWidth, int screenHeight);
	~WorldPositionController();

	void SetTargetEntity(Entity* entity, int screenX, int screenY);
	std::pair<int, int> GetScreenPosFromWorldPos(int worldX, int worldY) const;
	std::pair<std::pair<int, int>, std::pair<int, int>> GetWorldPosForEdgeOfScreen() const;

private:
	int _screenWidth;
	int _screenHeight;
	Entity* _targetEntity;
	int _entityScreenX;
	int _entityScreenY;
};

