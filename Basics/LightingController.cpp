#include "LightingController.h"
#include "EntityController.h"
#include <ctime>


LightingController::LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, 
										EntityController* entityController, TextureController* textureController, 
										TimeController* timeController, int screenWidth, int screenheight)
{
	_sdlRenderer = sdlRenderer;
	_renderController = renderController;
	_entityController = entityController;
	_textureController = textureController;
	_timeController = timeController;
	_screenWidth = screenWidth;
	_screenHeight = screenheight;

	_playerLight = _textureController->GetTexture("resources/playerlight.png");
	SDL_SetTextureBlendMode(_playerLight->RawTexture, SDL_BLENDMODE_BLEND);

	_testLightTexture = _textureController->GetTexture("resources/lightsource.png");
	SDL_SetTextureBlendMode(_testLightTexture->RawTexture, SDL_BLENDMODE_BLEND);

	_startOfDay = clock();
}

LightingController::~LightingController()
{
	delete _playerLight;
	delete _testLightTexture;
}

void LightingController::RenderLighting() const
{
	// Create a darkness texture
		// Full size of screen
		// Every pixel is black with full opacity (no transparency)
			// Increase the transparency to brighten the world
	// Use a light source image
		// Image colour is yellow
			// Colour of light source
		// Image uses transparency to show light
			// Lightest point is most transparent
			// Darkest point is least transparent
			// So middle is almost transparent, outside is fully opague
			// Middle shouldn't be fully transparent if you want the light source to have a colour
	// Render light source image on darkness texture
		// Additive blend mode
	// Render darkness texture
		// Multiply blend mode

	auto lightingTexture = SDL_CreateTexture(_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, 
											SDL_TEXTUREACCESS_TARGET, _screenWidth, _screenHeight);
	SDL_SetRenderTarget(_sdlRenderer, lightingTexture);

	SDL_Rect rect;
	rect.w = _screenWidth;
	rect.h = _screenHeight;
	rect.x = 0;
	rect.y = 0;

	auto brightness = GetDayBrightness();
	_renderController->DrawRectangle(&rect, brightness, brightness, brightness, 255);

	if (brightness < 230) {
		auto playerPos = _entityController->GetPlayerPosition();
		_renderController->RenderTexture(_playerLight, playerPos.first - (_playerLight->TextureRect->w / 2), playerPos.second - (_playerLight->TextureRect->h / 2));

		_renderController->RenderTexture(_testLightTexture, 100, 100);
		_renderController->RenderTexture(_testLightTexture, 300, 200);
		_renderController->RenderTexture(_testLightTexture, 1000, 400);
		_renderController->RenderTexture(_testLightTexture, 170, 700);
		_renderController->RenderTexture(_testLightTexture, 650, 600);
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
		return 255 * _timeController->GetPercentageOfDawnCompleted();
	case TimeOfDay::Dusk:
		return 255 - 255 * _timeController->GetPercentageOfDuskCompleted();
	default:
		return 255;
	}
}
