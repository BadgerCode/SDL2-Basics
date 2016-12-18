#include "LightingController.h"
#include "EntityController.h"
#include <ctime>


LightingController::LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, 
										TimeController* timeController, int screenWidth, int screenheight)
{
	_sdlRenderer = sdlRenderer;
	_renderController = renderController;
	_timeController = timeController;
	_screenWidth = screenWidth;
	_screenHeight = screenheight;

	_startOfDay = clock();
}

LightingController::~LightingController()
{
}

void LightingController::AddLightSource(LightSource* lightSource)
{
	_lightSources.push_back(lightSource);
}

void LightingController::RenderLighting() const
{
	auto lightingTexture = SDL_CreateTexture(_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, 
											SDL_TEXTUREACCESS_TARGET, _screenWidth, _screenHeight);
	SDL_SetRenderTarget(_sdlRenderer, lightingTexture);

	auto brightness = GetDayBrightness();
	RenderLightMap(brightness);

	if (brightness < 230) {
		RenderLightSources();
	}

	SDL_SetRenderTarget(_sdlRenderer, nullptr);
	SDL_SetTextureBlendMode(lightingTexture, SDL_BLENDMODE_MOD);
	SDL_RenderCopy(_sdlRenderer, lightingTexture, nullptr, nullptr);

	SDL_DestroyTexture(lightingTexture);
}

int LightingController::GetDayBrightness() const
{
	auto timeOfDay = _timeController->GetTimeOfDay();

	switch (timeOfDay)
	{
	case TimeOfDay::Night:
		return 0;
	case TimeOfDay::Dawn:
		return static_cast<int>(255 * _timeController->GetPercentageOfDawnCompleted());
	case TimeOfDay::Dusk:
		return static_cast<int>(255 - 255 * _timeController->GetPercentageOfDuskCompleted());
	default:
		return 255;
	}
}

void LightingController::RenderLightMap(int brightness) const
{
	SDL_Rect rect;
	rect.w = _screenWidth;
	rect.h = _screenHeight;
	rect.x = 0;
	rect.y = 0;

	_renderController->DrawScreenRectangle(&rect, brightness, brightness, brightness, 255);
}

void LightingController::RenderLightSources() const
{
	for (auto lightSource : _lightSources)
	{
		_renderController->RenderWorldTexture(lightSource->Texture, lightSource->_worldX, lightSource->_worldY);
	}
}
