#pragma once
#include <vector>
#include "RenderController.h"
#include "Entity.h"
#include <queue>

class Entity;

class EntityController
{
public:
	EntityController(RenderController* renderController);
	~EntityController();

	void AddEntity(Entity* entity);
	void UpdateAll();
	void RenderAll() const;
	std::vector<Entity*> FindInRange(int x, int y, int radius);
private:
	RenderController* _renderController;

	std::vector<Entity*> _entities;
	std::queue<Entity*> _newEntities;
};

