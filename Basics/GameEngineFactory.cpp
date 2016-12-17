#include "GameEngineFactory.h"
#include "TimeController.h"
#include "TileController.h"
#include "WorldPositionController.h"


GameEngineFactory::GameEngineFactory()
{
}

GameEngineFactory::~GameEngineFactory()
{
}

GameEngine* GameEngineFactory::Create(SDL_Renderer* sdlRenderer, int screenWidth, int screenHeight)
{
	auto textureController = new TextureController(sdlRenderer);
	auto keyboardController = new KeyboardController();
	auto worldPositionController = new WorldPositionController();
	auto renderController = new RenderController(sdlRenderer, textureController, worldPositionController, screenWidth, screenHeight);
	auto player = new Player(renderController, keyboardController,
							textureController->GetTexture("resources/player.png"),
							screenWidth / 2, screenHeight / 2,
							screenWidth, screenHeight);

	worldPositionController->SetTargetEntity(player, screenWidth / 2, screenHeight / 2);

	auto entityController = new EntityController(renderController, keyboardController, 
												textureController, screenWidth, 
												screenHeight, player);
	auto timeController = new TimeController();
	auto lightingController = new LightingController(sdlRenderer, renderController, entityController, textureController, timeController, screenWidth, screenHeight);
	auto tileController = new TileController(textureController, renderController, screenWidth, screenHeight);

	return new GameEngine(renderController, lightingController, keyboardController,
							textureController, entityController, timeController, tileController);
}
