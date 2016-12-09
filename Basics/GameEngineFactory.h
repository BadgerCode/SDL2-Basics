#pragma once
#include "GameEngine.h"

class GameEngineFactory
{
public:
	GameEngineFactory();
	~GameEngineFactory();

	static GameEngine* Create(SDL_Renderer* sdlRenderer, int screenWidth, int screenHeight);
};

