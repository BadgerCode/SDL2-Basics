#include "GameEngineFactory.h"



GameEngineFactory::GameEngineFactory()
{
}


GameEngineFactory::~GameEngineFactory()
{
}

GameEngine* GameEngineFactory::Create(const char* windowTitle, int screenWidth, int screenHeight)
{
	auto sdlWindow = SDL_CreateWindow(windowTitle,
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		screenWidth,
		screenHeight,
		SDL_WINDOW_OPENGL);
	auto sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED);
	auto renderController = new RenderController(sdlRenderer, screenWidth, screenHeight);

	return new GameEngine(sdlWindow, renderController, screenWidth, screenHeight);
}
