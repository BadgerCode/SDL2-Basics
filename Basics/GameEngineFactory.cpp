#include "GameEngineFactory.h"


GameEngineFactory::GameEngineFactory()
{
}

GameEngineFactory::~GameEngineFactory()
{
}

GameEngine* GameEngineFactory::Create(SDL_Renderer* sdlRenderer, int screenWidth, int screenHeight)
{
	auto renderController = new RenderController(sdlRenderer, screenWidth, screenHeight);
	auto keyboardController = new KeyboardController();
	auto textureController = new TextureController(sdlRenderer);
	auto entityController = new EntityController(renderController, keyboardController, 
													textureController, screenWidth, screenHeight);

	return new GameEngine(renderController, keyboardController, 
							textureController, entityController);
}
