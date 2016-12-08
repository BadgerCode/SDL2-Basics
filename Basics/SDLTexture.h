#pragma once

#include "SDL2/SDL_image.h"

class SDLTexture
{
public:
	SDLTexture(SDL_Texture* texture, int width, int height);
	~SDLTexture();

	SDL_Texture* RawTexture;
	SDL_Rect* TextureRect;
};

