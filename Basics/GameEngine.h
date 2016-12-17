#pragma once

#include "EntityController.h"
#include "KeyboardController.h"
#include "RenderController.h"
#include "TextureController.h"
#include "LightingController.h"
#include "TimeController.h"
#include "TileController.h"

class EntityController;

enum class GameState { PLAY, EXIT };

class GameEngine
{
public:
	GameEngine(RenderController* renderController, 
				LightingController* lightingController,
				KeyboardController* keyboardController,
				TextureController* textureController, 
				EntityController* entityController,
				TimeController* timeController,
				TileController* tileController);
	~GameEngine();
	void Start();

private :
	RenderController* _renderController;
	LightingController* _lightingController;
	KeyboardController* _keyboardController;
	TextureController* _textureController;
	EntityController* _entityController;
	TimeController* _timeController;
	TileController* _tileController;

	GameState _gameState;

	void LoadTextures() const;
	void CreateEntities() const;
	void GameLoop();
	void ProcessInput();
};

