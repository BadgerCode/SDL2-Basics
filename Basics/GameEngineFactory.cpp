#include "GameEngineFactory.h"
#include "TimeController.h"
#include "TileController.h"
#include "WorldPositionController.h"
#include "Player.h"


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
	auto worldPositionController = new WorldPositionController(screenWidth, screenHeight);
	auto timeController = new TimeController();

	auto renderController = new RenderController(sdlRenderer, textureController, worldPositionController, screenWidth, screenHeight);

	auto playerX = 500;
	auto playerY = 500;
	auto playerLight = textureController->GetTexture("resources/playerlight.png");
	SDL_SetTextureBlendMode(playerLight->RawTexture, SDL_BLENDMODE_BLEND);
	auto playerLightSource = new LightSource(playerLight, playerX, playerY);

	auto player = new Player(renderController, keyboardController,
							textureController->GetTexture("resources/player.png"),
							playerLightSource, playerX, playerY, screenWidth, screenHeight);

	worldPositionController->SetTargetEntity(player, screenWidth / 2, screenHeight / 2);

	auto entityController = new EntityController(renderController);
	entityController->AddEntity(player);

	auto lightingController = new LightingController(sdlRenderer, renderController, timeController, screenWidth, screenHeight);
	lightingController->AddLightSource(playerLightSource);

	auto tileController = new TileController(worldPositionController, textureController, renderController, 2000, 2000);

	return new GameEngine(renderController, lightingController, keyboardController,
							textureController, entityController, timeController, tileController);
}
