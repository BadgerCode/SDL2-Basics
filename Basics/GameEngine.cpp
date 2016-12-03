#include "GameEngine.h"



GameEngine::GameEngine()
{
	_sdlWindow = nullptr;
	_screenWidth = 400;
	_screenHeight = 400;
	_gameState = GameState::PLAY;

	_playerX = _screenWidth / 2;
	_playerY = _screenHeight / 2;
}

GameEngine::~GameEngine()
{
}

void GameEngine::Initialise()
{
	InitWindow();
	GameLoop();
}

void GameEngine::InitWindow()
{
	_sdlWindow = SDL_CreateWindow("Game engine",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		_screenWidth,
		_screenHeight,
		SDL_WINDOW_OPENGL);
	// TODO: check for errors when creating window (window == nullptr)

	_sdlRenderer = SDL_CreateRenderer(_sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	// TODO: Check for error

	SDL_RenderSetLogicalSize(_sdlRenderer, _screenWidth, _screenHeight);
}

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		ProcessInput();

		int speed = 3;
		_playerX += speed * (_playerMovement.Right - _playerMovement.Left);
		_playerY += speed * (_playerMovement.Down - _playerMovement.Up);
		
		ClearScreen();
		DrawThings();

		SDL_RenderPresent(_sdlRenderer);

		SDL_Delay(16);
	}
}

void GameEngine::ClearScreen() const
{
	SDL_SetRenderDrawColor(_sdlRenderer, 50, 120, 255, 255);
	SDL_RenderClear(_sdlRenderer);
}

void GameEngine::DrawThings() const
{
	SDL_Rect r;
	r.x = _playerX;
	r.y = _playerY;
	r.w = 25;
	r.h = 75;

	SDL_SetRenderDrawColor(_sdlRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(_sdlRenderer, &r);

	SDL_SetRenderDrawColor(_sdlRenderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(_sdlRenderer, &r);
}

void GameEngine::ProcessInput()
{
	SDL_Event sdlEvent;
	while(SDL_PollEvent(&sdlEvent))
	{
		if(sdlEvent.type == SDL_QUIT)
		{
			_gameState = GameState::EXIT;
		}
		else if(sdlEvent.type == SDL_KEYDOWN)
		{
			switch(sdlEvent.key.keysym.sym)
			{
			case SDLK_d:
				_playerMovement.Right = true;
				break;
			case SDLK_a:
				_playerMovement.Left = true;
				break;
			case SDLK_w:
				_playerMovement.Up = true;
				break;
			case SDLK_s:
				_playerMovement.Down = true;
				break;
			default:
				break;
			}
		}
		else if (sdlEvent.type == SDL_KEYUP)
		{
			switch (sdlEvent.key.keysym.sym)
			{
			case SDLK_d:
				_playerMovement.Right = false;
				break;
			case SDLK_a:
				_playerMovement.Left = false;
				break;
			case SDLK_w:
				_playerMovement.Up = false;
				break;
			case SDLK_s:
				_playerMovement.Down = false;
				break;
			default:
				break;
			}
		}
	}
}
