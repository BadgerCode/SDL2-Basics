#include "LightSource.h"


LightSource::LightSource(RenderableSDLTexture* texture, int worldX, int worldY)
{
	Texture = texture;
	_worldX = worldX;
	_worldY = worldY;
}

LightSource::~LightSource()
{
	delete Texture;
}