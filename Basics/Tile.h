#pragma once
#include "RenderableSDLTexture.h"
#include "RenderController.h"

class Tile
{
public:
	Tile(RenderController* renderController, RenderableSDLTexture* texture, int worldX, int worldY);
	~Tile();

	void Render() const;
private:
	int _worldX;
	int _worldY;

	RenderController* _renderController;
	RenderableSDLTexture* _texture;
};

