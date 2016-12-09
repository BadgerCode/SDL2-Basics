#pragma once

class EntityController;

class Entity
{
public:
	virtual ~Entity() { }

	virtual void Update() = 0;
	virtual void Render() const = 0;
protected:
	Entity(EntityController* entityController): _entityController(entityController){ }
	EntityController* _entityController;
};
