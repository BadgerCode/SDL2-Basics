#include "GameEngine.h"


GameEngine::GameEngine(RenderController* renderController, 
						LightingController* lightingController,
						KeyboardController* keyboardController, 
						TextureController* textureController, 
						EntityController* entityController,
						TimeController* timeController)
{
	_renderController = renderController;
	_lightingController = lightingController;
	_keyboardController = keyboardController;
	_textureController = textureController;
	_entityController = entityController;
	_timeController = timeController;

	_gameState = GameState::PLAY;
}

GameEngine::~GameEngine()
{
	delete _renderController;
	delete _textureController;
	delete _entityController;
	delete _keyboardController;
}

void GameEngine::Start()
{
	LoadTextures();
	CreateEntities();
	GameLoop();
}

void GameEngine::LoadTextures() const
{
	_textureController->PreloadTexture("resources/grass.png");
	_textureController->PreloadTexture("resources/lightsource.png");
	_textureController->PreloadTexture("resources/player.png");
	_textureController->PreloadTexture("resources/playerlight.png");
	_textureController->PreloadTexture("resources/skeleton.png");
	_renderController->PreloadBackground();
}

void GameEngine::CreateEntities() const
{
	_entityController->AddEnemy(10, 10);
	_entityController->AddEnemy(120, 200);
	_entityController->AddEnemy(900, 300);
	_entityController->AddEnemy(250, 500);
}

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		_timeController->Update();

		ProcessInput();

		_entityController->UpdateAll();
		
		_renderController->ClearScreen();
		_renderController->DrawBackground();

		_entityController->RenderAll();

		_lightingController->RenderLighting();
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
			_keyboardController->ProcessEvent(&sdlEvent);
		}
	}
}