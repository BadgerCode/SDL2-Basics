#include "WorldPositionController.h"



WorldPositionController::WorldPositionController(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

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

std::pair<std::pair<int, int>, std::pair<int, int>> WorldPositionController::GetWorldPosForEdgeOfScreen() const
{
	auto entityPos = _targetEntity->GetPosition();

	auto left = entityPos.first - _screenWidth / 2;
	auto right = entityPos.first + _screenWidth / 2;
	auto top = entityPos.second - _screenHeight / 2;
	auto bottom = entityPos.second + _screenHeight / 2;

	return std::pair<std::pair<int, int>, std::pair<int, int>>(std::pair<int, int>(left, top), std::pair<int, int>(right, bottom));
}
