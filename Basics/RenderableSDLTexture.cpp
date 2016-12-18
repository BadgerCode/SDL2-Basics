#include "RenderableSDLTexture.h"


RenderableSDLTexture::RenderableSDLTexture(SDL_Texture* texture, int width, int height)
{
	RawTexture = texture;

	TextureRect = new SDL_Rect();
	TextureRect->w = width;
	TextureRect->h = height;
}

RenderableSDLTexture::~RenderableSDLTexture()
{
	
}
