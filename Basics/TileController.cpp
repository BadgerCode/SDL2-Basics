#include "TileController.h"



TileController::TileController(TextureController* textureController, RenderController* renderController, int worldWidth, int worldHeight)
{
	_renderController = renderController;

	auto tilesWidth = ceil(static_cast<double>(worldWidth) / TileWidth);
	auto tilesHeight = ceil(static_cast<double>(worldHeight) / TileHeight);

	for(auto y = 0; y < tilesHeight; y++)
	{
		_tiles.push_back(std::vector<Tile*>(tilesWidth));
		for(auto x = 0; x < tilesWidth; x++)
		{
			_tiles[y][x] = new Tile(_renderController, textureController->GetTexture("resources/grass.png"), x * TileWidth, y * TileHeight);
		}
	}
}


TileController::~TileController()
{
}

void TileController::Render() const
{
	for(auto i = 0; i < _tiles.size(); i++)
	{
		for(auto j = 0; j < _tiles[i].size(); j++)
		{
			if(_tiles[i][j] != nullptr)
			{
				_tiles[i][j]->Render();
			}
		}
	}
}
