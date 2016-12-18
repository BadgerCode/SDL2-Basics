#pragma once
#include "RenderController.h"
#include "TimeController.h"
#include <ctime>
#include "LightSource.h"

class TimeController;
class EntityController;

class LightingController
{
public:
	LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, 
						TextureController* textureController, TimeController* timeController, 
						int screenWidth, int screenheight);
	~LightingController();

	void AddLightSource(LightSource* lightSource);
	void RenderLighting() const;

private:
	SDL_Renderer* _sdlRenderer;
	RenderController* _renderController;
	TextureController* _textureController;
	TimeController* _timeController;
	int _screenWidth;
	int _screenHeight;

	std::vector<LightSource*> _lightSources;

	RenderableSDLTexture* _testLightTexture;

	clock_t _startOfDay;
	int GetDayBrightness() const;

	void RenderLightMap(int brightness) const;
	void RenderLightSources() const;
};

