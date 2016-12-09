#pragma once

class EntityController;

class Entity
{
protected:
	Entity(EntityController* entityController): _entityController(entityController){ }
	EntityController* _entityController;
};
