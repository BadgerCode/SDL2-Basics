#pragma once
#include <utility>

class EntityController;

class Entity
{
public:
	virtual ~Entity() { }

	virtual void Update() = 0;
	virtual void Render() const = 0;
	virtual std::pair<int, int> GetPosition() const = 0;
	virtual void SetPosition(int worldX, int worldY) = 0;
protected:
	Entity() { }
};
