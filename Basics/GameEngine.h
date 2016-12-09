#pragma once

#include "EntityController.h"
#include "KeyboardController.h"
#include "RenderController.h"
#include "TextureController.h"

class EntityController;

enum class GameState { PLAY, EXIT };

class GameEngine
{
public:
	GameEngine(RenderController* renderController, 
				KeyboardController* keyboardController,
				TextureController* textureController, EntityController* entityController);
	~GameEngine();
	void Start();

private :
	RenderController* _renderController;
	KeyboardController* _keyboardController;
	TextureController* _textureController;
	EntityController* _entityController;

	GameState _gameState;

	void LoadTextures() const;
	void CreateEntities() const;
	void GameLoop();
	void ProcessInput();
};

