#include "WorldPositionController.h"



WorldPositionController::WorldPositionController()
{
	_targetEntity = nullptr;
	_entityScreenX = 0;
	_entityScreenY = 0;
}


WorldPositionController::~WorldPositionController()
{
}

void WorldPositionController::SetTargetEntity(Entity* entity, int screenX, int screenY)
{
	_targetEntity = entity;
	_entityScreenX = screenX;
	_entityScreenY = screenY;
}

std::pair<int, int> WorldPositionController::GetScreenPosFromWorldPos(int worldX, int worldY) const
{
	auto entityPos = _targetEntity->GetPosition();

	auto xDiff = entityPos.first - worldX;
	auto yDiff = entityPos.second - worldY;

	return std::pair<int, int>(_entityScreenX - xDiff, _entityScreenY - yDiff);
}
