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

void LightSource::SetWorldPosition(int worldX, int worldY)
{
	_worldX = worldX;
	_worldY = worldY;
}

std::pair<int, int> LightSource::GetWorldPosition() const
{
	return std::pair<int, int>(_worldX - Texture->TextureRect->w / 2, _worldY - Texture->TextureRect->h / 2);
}
