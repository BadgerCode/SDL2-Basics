#pragma once
#include "RenderController.h"

class EntityController;

class LightingController
{
public:
	LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, EntityController* entityController, TextureController* textureController, int screenWidth, int screenheight);
	~LightingController();

	void RenderLighting();

private:
	SDL_Renderer* _sdlRenderer;
	RenderController* _renderController;
	EntityController* _entityController;
	TextureController* _textureController;
	int _screenWidth;
	int _screenHeight;

	RenderableSDLTexture* _testLightTexture;
	RenderableSDLTexture* _playerLight;
};

