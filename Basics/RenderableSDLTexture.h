#pragma once

#include "SDL2/SDL_image.h"

class RenderableSDLTexture
{
public:
	RenderableSDLTexture(SDL_Texture* texture, int width, int height);
	~RenderableSDLTexture();

	SDL_Texture* RawTexture;
	SDL_Rect* TextureRect;
};

