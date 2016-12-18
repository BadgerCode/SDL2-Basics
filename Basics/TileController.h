#pragma once
#include "Tile.h"

class TileController
{
public:
	TileController(TextureController* textureController, RenderController* renderController, int worldWidth, int worldHeight);
	~TileController();

	void Render() const;
private:
	RenderController* _renderController;

	std::vector<std::vector<Tile*>> _tiles;
	static const int TileWidth = 20;
	static const int TileHeight = 20;
};

