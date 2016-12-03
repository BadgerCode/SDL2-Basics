#pragma once

#include "SDL2/SDL.h"

enum class GameState { PLAY, EXIT };

struct PlayerMovement
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void Initialise();

private :
	SDL_Window* _sdlWindow;
	SDL_Renderer* _sdlRenderer;
	int _screenWidth;
	int _screenHeight;
	GameState _gameState;

	PlayerMovement _playerMovement;
	int _playerX;
	int _playerY;

	void InitWindow();
	void GameLoop();
	void ClearScreen() const;
	void DrawThings() const;
	void ProcessInput();
};

