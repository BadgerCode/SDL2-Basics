#pragma once

#include "SDL2/SDL.h"
#include "RenderController.h"
#include "Player.h"

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
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	PlayerMovement _playerMovement;
	Player* _player;

	void GameLoop();
	void ProcessInput();
};

