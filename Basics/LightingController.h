#pragma once
#include "RenderController.h"
#include "TimeController.h"
#include <ctime>

class TimeController;
class EntityController;

class LightingController
{
public:
	LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, 
						EntityController* entityController, TextureController* textureController, 
						TimeController* timeController, int screenWidth, int screenheight);
	~LightingController();

	void RenderLighting() const;

private:
	SDL_Renderer* _sdlRenderer;
	RenderController* _renderController;
	EntityController* _entityController;
	TextureController* _textureController;
	TimeController* _timeController;
	int _screenWidth;
	int _screenHeight;

	RenderableSDLTexture* _testLightTexture;
	RenderableSDLTexture* _playerLight;

	clock_t _startOfDay;
	int GetDayBrightness() const;
};

