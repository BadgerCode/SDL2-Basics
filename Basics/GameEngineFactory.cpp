#include "GameEngineFactory.h"
#include "TimeController.h"


GameEngineFactory::GameEngineFactory()
{
}

GameEngineFactory::~GameEngineFactory()
{
}

GameEngine* GameEngineFactory::Create(SDL_Renderer* sdlRenderer, int screenWidth, int screenHeight)
{
	auto textureController = new TextureController(sdlRenderer);
	auto renderController = new RenderController(sdlRenderer, textureController, screenWidth, screenHeight);
	auto keyboardController = new KeyboardController();
	auto entityController = new EntityController(renderController, keyboardController, 
													textureController, screenWidth, screenHeight);
	auto timeController = new TimeController();
	auto lightingController = new LightingController(sdlRenderer, renderController, entityController, textureController, timeController, screenWidth, screenHeight);

	return new GameEngine(renderController, lightingController, keyboardController,
							textureController, entityController, timeController);
}
