#include "GameEngine.h"


GameEngine::GameEngine(SDL_Window* sdlWindow, RenderController* renderController, TextureController* textureController, int screenWidth, int screenHeight)
{
	_sdlWindow = sdlWindow;
	_renderController = renderController;
	_textureController = textureController;

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_gameState = GameState::PLAY;

	_player = new Player(renderController, textureController->GetTexture("resources/player.png"), _screenWidth / 2, _screenHeight / 2, _screenWidth, _screenHeight);

	_enemies.push_back(new Enemy(renderController, textureController->GetTexture("resources/skeleton.png"), 10, 10, _screenWidth, _screenHeight));
	_enemies.push_back(new Enemy(renderController, textureController->GetTexture("resources/skeleton.png"), 120, 200, _screenWidth, _screenHeight));
	_enemies.push_back(new Enemy(renderController, textureController->GetTexture("resources/skeleton.png"), 900, 300, _screenWidth, _screenHeight));
	_enemies.push_back(new Enemy(renderController, textureController->GetTexture("resources/skeleton.png"), 250, 500, _screenWidth, _screenHeight));
}

GameEngine::~GameEngine()
{
	delete _renderController;
	delete _textureController;
	delete _player;
	for (auto enemy : _enemies) { delete enemy; }
}

bool GameEngine::Start()
{
	if(_sdlWindow == nullptr || _renderController == nullptr)
	{
		return false;
	}

	LoadTextures();
	GameLoop();
	return true;
}

void GameEngine::LoadTextures() const
{
	_textureController->PreloadTexture("resources/player.png");
	_textureController->PreloadTexture("resources/skeleton.png");
}

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		ProcessInput();

		_player->ProcessInput(_keyboardController.GetUserInput());
		for (auto enemy : _enemies) { enemy->Update(); }
		
		_renderController->ClearScreen();

		_player->Render();
		for (auto enemy : _enemies) {enemy->Render(); }

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