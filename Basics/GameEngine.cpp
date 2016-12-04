#include "GameEngine.h"


GameEngine::GameEngine(SDL_Window* sdlWindow, RenderController* renderController, int screenWidth, int screenHeight)
{
	_sdlWindow = sdlWindow;
	_renderController = renderController;

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_gameState = GameState::PLAY;

	_player = new Player(renderController, _screenWidth / 2, _screenHeight / 2);
}

GameEngine::~GameEngine()
{
	delete _renderController;
	delete _player;
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

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		ProcessInput();

		_player->ProcessInput(_keyboardController.GetUserInput());
		
		_renderController->ClearScreen();
		_player->Render();
		_renderController->UpdateScreen();

		SDL_Delay(16); // Gives us 60 FPS. Doesn't take into account how long this "frame" took to process.
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
			_keyboardController.ProcessEvent(&sdlEvent);
		}
	}
}

const char* GameEngine::GetLastError()
{
	return SDL_GetError();
}