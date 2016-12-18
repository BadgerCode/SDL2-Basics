#include "EntityController.h"


EntityController::EntityController(RenderController* renderController)
{
	_renderController = renderController;
}

EntityController::~EntityController()
{
	for (auto entity : _entities) { delete entity; }
}

void EntityController::AddEntity(Entity* entity)
{
	_newEntities.push(entity);
}

void EntityController::UpdateAll()
{
	for (auto entity : _entities) { entity->Update(); }

	while(!_newEntities.empty())
	{
		_entities.push_back(_newEntities.front());
		_newEntities.pop();
	}
}

void EntityController::RenderAll() const
{
	for (auto entity : _entities) { entity->Render(); }
}

std::vector<Entity*> EntityController::FindInRange(int x, int y, int radius)
{
	std::vector<Entity*> entitiesInRange;
	for (auto entity : _entities)
	{
		auto entityPos = entity->GetPosition();
		auto xDiff = x - entityPos.first;
		auto yDiff = y - entityPos.second;
		auto distance = sqrt(xDiff*xDiff + yDiff*yDiff);

		if(distance <= radius)
		{
			entitiesInRange.push_back(entity);
		}
	}
	return entitiesInRange;
}
