#include "SDLTexture.h"


SDLTexture::SDLTexture(SDL_Texture* texture, int width, int height)
{
	RawTexture = texture;

	TextureRect = new SDL_Rect();
	TextureRect->w = width;
	TextureRect->h = height;
}

SDLTexture::~SDLTexture()
{
}
