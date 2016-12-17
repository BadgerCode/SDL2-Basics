#pragma once
#include <utility>
#include "Entity.h"

class WorldPositionController
{
public:
	WorldPositionController();
	~WorldPositionController();

	void SetTargetEntity(Entity* entity, int screenX, int screenY);
	std::pair<int, int> GetScreenPosFromWorldPos(int worldX, int worldY) const;

private:
	Entity* _targetEntity;
	int _entityScreenX;
	int _entityScreenY;
};

