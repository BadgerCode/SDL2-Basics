#include "Tile.h"



Tile::Tile(RenderController* renderController, RenderableSDLTexture* texture, int worldX, int worldY)
{
	_renderController = renderController;
	_texture = texture;
	_worldX = worldX;
	_worldY = worldY;
}


Tile::~Tile()
{
}

void Tile::Render() const
{
	_renderController->RenderWorldTexture(_texture, _worldX, _worldY);
}
