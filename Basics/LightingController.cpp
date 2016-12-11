#include "LightingController.h"
#include "EntityController.h"
#include <ctime>


LightingController::LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, 
										EntityController* entityController, TextureController* textureController, 
										int screenWidth, int screenheight)
{
	_sdlRenderer = sdlRenderer;
	_renderController = renderController;
	_entityController = entityController;
	_textureController = textureController;
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

int LightingController::GetDayBrightness()
{
	auto secondsPerNight = 10;
	auto secondsPerDawn = 2;
	auto secondsPerDaylight = 10;
	auto secondsPerDusk = 2;
	auto secondsPerDay = secondsPerNight + secondsPerDawn + secondsPerDaylight + secondsPerDusk;

	auto currentHour = (static_cast<double>(clock()) - _startOfDay) / CLOCKS_PER_SEC;
	if(currentHour >= secondsPerDay)
	{
		_startOfDay = clock();
		currentHour = 0;
	}

	auto isNighttime = currentHour < (secondsPerNight / 2) || currentHour >= secondsPerDay - (secondsPerNight / 2);
	if (isNighttime)
	{
		return 0;
	}

	auto isDawn = currentHour < (secondsPerNight / 2) + secondsPerDawn;
	if(isDawn)
	{
		auto timeInDawn = currentHour - (secondsPerNight / 2);
		return 255 * (static_cast<double>(timeInDawn) / secondsPerDawn);
	}

	auto duskStartTime = secondsPerDay - (secondsPerNight / 2) - secondsPerDusk;
	auto isDusk = currentHour >= duskStartTime;
	if(isDusk)
	{
		auto timeInDusk = currentHour - duskStartTime;
		return 255 - 255 * (static_cast<double>(timeInDusk) / secondsPerDusk);
	}

	
	return 255;
}

void LightingController::RenderLighting()
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

	if (brightness < 240) {
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
