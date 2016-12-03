#pragma once
#include "GameEngine.h"

class GameEngineFactory
{
public:
	GameEngineFactory();
	~GameEngineFactory();

	static GameEngine* Create(const char* windowTitle, int screenWidth, int screenHeight);
};

