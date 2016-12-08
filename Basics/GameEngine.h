#pragma once

#include "SDL2/SDL.h"

#include "Enemy.h"
#include "KeyboardController.h"
#include "Player.h"
#include "RenderController.h"
#include <vector>

enum class GameState { PLAY, EXIT };

class GameEngine
{
public:
	GameEngine(SDL_Window* sdlWindow, RenderController* renderController, int screenWidth, int screenHeight);
	~GameEngine();
	bool Start();
	static const char* GetLastError();

private :
	SDL_Window* _sdlWindow;
	RenderController* _renderController;
	KeyboardController _keyboardController;

	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	PlayerMovement _playerMovement;
	Player* _player;

	std::vector<Enemy*> _enemies;

	void GameLoop();
	void ProcessInput();
};

