#pragma once
#include "RenderController.h"

class LightingController
{
public:
	LightingController(SDL_Renderer* sdlRenderer, RenderController* renderController, TextureController* textureController, int screenWidth, int screenheight);
	~LightingController();

	void RenderLighting();

private:
	SDL_Renderer* _sdlRenderer;
	RenderController* _renderController;
	TextureController* _textureController;
	int _screenWidth;
	int _screenHeight;

	RenderableSDLTexture* _playerLight;
};

