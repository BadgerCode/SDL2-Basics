#include "GameEngine.h"
#include <chrono>
#include "Enemy.h"


GameEngine::GameEngine(RenderController* renderController, 
						LightingController* lightingController,
						KeyboardController* keyboardController, 
						TextureController* textureController, 
						EntityController* entityController,
						TimeController* timeController,
						TileController* tileController)
{
	_renderController = renderController;
	_lightingController = lightingController;
	_keyboardController = keyboardController;
	_textureController = textureController;
	_entityController = entityController;
	_timeController = timeController;
	_tileController = tileController;

	_gameState = GameState::PLAY;

	auto fps = 60;
	_secondsPerFrame = floor(1000 / fps);

	_testLightTexture = nullptr;
}

GameEngine::~GameEngine()
{
	delete _renderController;
	delete _textureController;
	delete _entityController;
	delete _keyboardController;
	delete _testLightTexture;
}

void GameEngine::Start()
{
	LoadTextures();
	CreateEntities();
	AddLightSources();
	GameLoop();
}

void GameEngine::LoadTextures() const
{
	_textureController->PreloadTexture("resources/grass.png");
	_textureController->PreloadTexture("resources/lightsource.png");
	_textureController->PreloadTexture("resources/player.png");
	_textureController->PreloadTexture("resources/playerlight.png");
	_textureController->PreloadTexture("resources/skeleton.png");
}

void GameEngine::CreateEntities() const
{
	for(int i = 0; i < 30; i++)
	{
		auto enemy = new Enemy(_renderController, _textureController->GetTexture("resources/skeleton.png"));
		enemy->SetPosition(rand() % 20 * 100, rand() % 20 * 100);
		_entityController->AddEntity(enemy);
	}
}

void GameEngine::AddLightSources()
{
	_testLightTexture = _textureController->GetTexture("resources/lightsource.png");
	SDL_SetTextureBlendMode(_testLightTexture->RawTexture, SDL_BLENDMODE_BLEND);

	for (int i = 0; i < 20; i++)
	{
		_lightingController->AddLightSource(new LightSource(_testLightTexture, rand() % 200 * 10, rand() % 200 * 10));
	}
}

void GameEngine::GameLoop()
{
	while(_gameState != GameState::EXIT)
	{
		auto startTime = std::chrono::high_resolution_clock::now();
		_timeController->Update();

		ProcessInput();

		_entityController->UpdateAll();
		
		_renderController->ClearScreen();
		_tileController->Render();

		_entityController->RenderAll();

		_lightingController->RenderLighting();
		_renderController->UpdateScreen();

		auto duration = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - startTime).count() * 1000;
		SDL_Delay(static_cast<Uint32>(std::max(static_cast<double>(0), _secondsPerFrame - duration)));
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