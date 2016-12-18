#include "TileController.h"
#include <algorithm>


TileController::TileController(WorldPositionController* worldPositionController, 
								TextureController* textureController, 
								RenderController* renderController, 
								int worldWidth, int worldHeight)
{
	_worldPositionController = worldPositionController;
	_renderController = renderController;

	auto tilesWidth = static_cast<int>(ceil(static_cast<double>(worldWidth) / TileWidth));
	auto tilesHeight = static_cast<int>(ceil(static_cast<double>(worldHeight) / TileHeight));

	auto texture = textureController->GetTexture("resources/grass.png");
	auto tileHalfWidth = TileWidth / 2;
	auto tileHalfHeight = TileHeight / 2;

	for(auto y = 0; y < tilesHeight; y++)
	{
		_tiles.push_back(std::vector<Tile*>(tilesWidth));
		for(auto x = 0; x < tilesWidth; x++)
		{
			_tiles[y][x] = new Tile(_renderController, texture, x * TileWidth + tileHalfWidth, y * TileHeight + tileHalfHeight);
		}
	}
}


TileController::~TileController()
{
}

void TileController::Render() const
{
	if(!_tiles.size())
	{
		return;
	}

	auto screenCorners = _worldPositionController->GetWorldPosForEdgeOfScreen();
	auto firstRow = static_cast<int>(std::max(static_cast<double>(0), floor(static_cast<double>(screenCorners.first.second) / TileHeight)));
	auto lastRow = static_cast<int>(std::min(static_cast<double>(_tiles.size() - 1), ceil(static_cast<double>(screenCorners.second.second) / TileHeight)));

	auto firstCol = static_cast<int>(std::max(static_cast<double>(0), floor(static_cast<double>(screenCorners.first.first) / TileWidth)));
	auto lastCol = static_cast<int>(std::min(static_cast<double>(_tiles[0].size() - 1), ceil(static_cast<double>(screenCorners.second.first) / TileWidth)));

	for(auto i = firstRow; i <= lastRow; i++)
	{
		for(auto j = firstCol; j <= lastCol; j++)
		{
			auto tile = _tiles[i][j];
			if(tile != nullptr)
			{
				tile->Render();
			}
		}
	}
}
