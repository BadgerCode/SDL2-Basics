#pragma once
#include "RenderableSDLTexture.h"

class LightSource
{
public:
	LightSource(RenderableSDLTexture* texture, int worldX, int worldY);
	~LightSource();

	RenderableSDLTexture* Texture;
	int _worldX;
	int _worldY;
};

