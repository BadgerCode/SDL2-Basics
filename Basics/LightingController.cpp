#include "LightingController.h"



LightingController::LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, TextureController* textureController, int screenWidth, int screenheight)
{
	_sdlRenderer = sdlRenderer;
	_renderController = renderController;
	_textureController = textureController;
	_screenWidth = screenWidth;
	_screenHeight = screenheight;

	_playerLight = _textureController->GetTexture("resources/playerlight.png");
	SDL_SetTextureBlendMode(_playerLight->RawTexture, SDL_BLENDMODE_BLEND);
}

LightingController::~LightingController()
{
}

void LightingController::RenderLighting()
{
	// Create a darkness texture
		// Full size of screen
		// Every pixel is black with full opacity (no transparency)
			// Increase the transparency to brighten the world
		// Blend mode to multiply?
	// Use a light source image
		// Image colour is yellow
			// Colour of light source
		// Image uses transparency to show light
			// Lightest point is most transparent
			// Darkest point is least transparent
			// So middle is almost transparent, outside is fully opague
			// Middle shouldn't be fully transparent if you want the light source to have a colour
	// Render light source image on darkness texture
	// Render darkness texture

	auto lightingTexture = SDL_CreateTexture(_sdlRenderer, SDL_PIXELFORMAT_RGBA8888, 
											SDL_TEXTUREACCESS_TARGET, _screenWidth, _screenHeight);
	SDL_SetRenderTarget(_sdlRenderer, lightingTexture);

	SDL_Rect rect;
	rect.w = _screenWidth;
	rect.h = _screenHeight;
	rect.x = 0;
	rect.y = 0;
	_renderController->DrawRectangle(&rect, 0, 0, 0, 255);

	_renderController->RenderTexture(_playerLight, _screenWidth / 2 - (_playerLight->TextureRect->w / 2), _screenHeight / 2 - (_playerLight->TextureRect->h / 2));

	auto lightTexture = _textureController->GetTexture("resources/lightsource.png");
	SDL_SetTextureBlendMode(lightTexture->RawTexture, SDL_BLENDMODE_BLEND);
	_renderController->RenderTexture(lightTexture, 100, 100);
	_renderController->RenderTexture(lightTexture, 300, 200);
	_renderController->RenderTexture(lightTexture, 1000, 400);
	_renderController->RenderTexture(lightTexture, 170, 700);
	_renderController->RenderTexture(lightTexture, 650, 600);

	SDL_SetRenderTarget(_sdlRenderer, nullptr);
	SDL_SetTextureBlendMode(lightingTexture, SDL_BLENDMODE_MOD);
	SDL_RenderCopy(_sdlRenderer, lightingTexture, nullptr, nullptr);
	SDL_DestroyTexture(lightingTexture);
}
