#pragma once
#include "Tile.h"
#include "TextureController.h"

class TileController
{
public:
	TileController(WorldPositionController* worldPositionController, 
					TextureController* textureController, 
					RenderController* renderController, 
					int worldWidth, int worldHeight);
	~TileController();

	void Render() const;
private:
	WorldPositionController* _worldPositionController;
	RenderController* _renderController;

	std::vector<std::vector<Tile*>> _tiles;
	static const int TileWidth = 20;
	static const int TileHeight = 20;
};

