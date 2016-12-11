#include "RenderController.h"



RenderController::RenderController(SDL_Renderer* renderer, TextureController* textureController, int screenWidth, int screenHeight)
{
	_sdlRenderer = renderer;
	_textureController = textureController;

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	SDL_RenderSetLogicalSize(_sdlRenderer, screenWidth, screenHeight);
}


RenderController::~RenderController()
{
}

void RenderController::ClearScreen() const
{
	SDL_SetRenderDrawColor(_sdlRenderer, 50, 120, 255, 255);
	SDL_RenderClear(_sdlRenderer);
}

void RenderController::UpdateScreen() const
{
	SDL_RenderPresent(_sdlRenderer);
}

void RenderController::PreloadBackground()
{
	int tilesHeight = ceil(static_cast<double>(_screenHeight) / 100);
	int tilesWidth = ceil(static_cast<double>(_screenWidth) / 100);

	for(auto r = 0; r < tilesHeight; r++)
	{
		_backgroundTiles.push_back(std::vector<RenderableSDLTexture*>(tilesWidth));

		for(auto c = 0; c < tilesWidth; c++)
		{
			_backgroundTiles[r][c] = _textureController->GetTexture("resources/grass.png");
		}
	}
}

void RenderController::DrawBackground() const
{
	int rows = _backgroundTiles.size();
	int cols = _backgroundTiles[0].size();

	for(auto r = 0; r < rows; r++)
	{
		for(auto c = 0; c < cols; c++)
		{
			RenderTexture(_backgroundTiles[r][c], c * 100, r * 100);
		}
	}
}

void RenderController::RenderTexture(RenderableSDLTexture* texture, int x, int y) const
{
	texture->TextureRect->x = x;
	texture->TextureRect->y = y;

	SDL_RenderCopy(_sdlRenderer, texture->RawTexture, nullptr, texture->TextureRect);
}

void RenderController::DrawRectangle(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderFillRect(_sdlRenderer, rect);
}

void RenderController::DrawRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderDrawRect(_sdlRenderer, rect);
}
