#include "GameEngine.h"


GameEngine::GameEngine(SDL_Window* sdlWindow, RenderController* renderController, int screenWidth, int screenHeight)
{
	_sdlWindow = sdlWindow;
	_renderController = renderController;

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_gameState = GameState::PLAY;

	_playerX = _screenWidth / 2;
	_playerY = _screenHeight / 2;
}

GameEngine::~GameEngine()
{
	delete _renderController;
}

bool GameEngine::Start()
{
	if(_sdlWindow == nullptr || _renderController == nullptr)
	{
		return false;
	}

	GameLoop();
	return true;
}

const char* GameEngine::GetLastError()
{
	return SDL_GetError();
}

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		ProcessInput();

		int speed = 3;
		_playerX += speed * (_playerMovement.Right - _playerMovement.Left);
		_playerY += speed * (_playerMovement.Down - _playerMovement.Up);
		
		_renderController->ClearScreen();
		_renderController->DrawPlayer(_playerX, _playerY);
		_renderController->UpdateScreen();

		SDL_Delay(16);
	}
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
		else if(sdlEvent.type == SDL_KEYDOWN || sdlEvent.type == SDL_KEYUP)
		{
			bool keyPressed = sdlEvent.type == SDL_KEYDOWN;
			switch(sdlEvent.key.keysym.sym)
			{
			case SDLK_d:
				_playerMovement.Right = keyPressed;
				break;
			case SDLK_a:
				_playerMovement.Left = keyPressed;
				break;
			case SDLK_w:
				_playerMovement.Up = keyPressed;
				break;
			case SDLK_s:
				_playerMovement.Down = keyPressed;
				break;
			default:
				break;
			}
		}
	}
}
