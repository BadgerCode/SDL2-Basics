#pragma once
#include <vector>
#include "TextureController.h"
#include "Player.h"
#include <queue>

class Entity;

class EntityController
{
public:
	EntityController(RenderController* renderController, KeyboardController* keyboardController, 
					 TextureController* textureController, int screenWidth, int screenHeight);
	~EntityController();

	void AddEnemy(int spawnX, int spawnY);
	void UpdateAll();
	void RenderAll();
	std::vector<Entity*> FindInRange(int x, int y, int radius);

private:
	RenderController* _renderController;
	TextureController* _textureController;
	KeyboardController* _keyboardController;

	Player* _player;
	std::vector<Entity*> _entities;
	std::queue<Entity*> _newEntities;
	int _screenWidth;
	int _screenHeight;
};

