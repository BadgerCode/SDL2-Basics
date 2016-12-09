#pragma once
#include <vector>
#include "TextureController.h"
#include "Player.h"

class Enemy;

class EntityController
{
public:
	EntityController(RenderController* renderController, KeyboardController* keyboardController, 
					 TextureController* textureController, int screenWidth, int screenHeight);
	~EntityController();

	void AddEnemy(int spawnX, int spawnY);
	void UpdateAll();
	void RenderAll();

private:
	RenderController* _renderController;
	TextureController* _textureController;
	KeyboardController* _keyboardController;

	Player* _player;
	std::vector<Enemy*> _entities;
	int _screenWidth;
	int _screenHeight;
};

