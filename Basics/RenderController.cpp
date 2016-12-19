#include "RenderController.h"
#include <SDL2/SDL_ttf.h>


RenderController::RenderController(SDL_Renderer* renderer, WorldPositionController* worldPositionController, 
									int screenWidth, int screenHeight)
{
	_sdlRenderer = renderer;
	_worldPositionController = worldPositionController;

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

void RenderController::RenderWorldTexture(RenderableSDLTexture* texture, int x, int y) const
{
	auto screenPos = _worldPositionController->GetScreenPosFromWorldPos(x, y);
	auto screenX = screenPos.first - texture->TextureRect->w / 2;
	auto screenY = screenPos.second - texture->TextureRect->h / 2;

	if (screenX > _screenWidth || screenY > _screenHeight)
	{
		return;
	}

	if(screenX + texture->TextureRect->w < 0 || screenY + texture->TextureRect->h < 0)
	{
		return;
	}

	RenderScreenTexture(texture, screenX, screenY);
}

void RenderController::RenderScreenTexture(RenderableSDLTexture* texture, int x, int y) const
{
	texture->TextureRect->x = x;
	texture->TextureRect->y = y;

	SDL_RenderCopy(_sdlRenderer, texture->RawTexture, nullptr, texture->TextureRect);
}

void RenderController::RenderScreenText(TTF_Font* font, const char* text, SDL_Color color, int x, int y) const
{
	auto surface = TTF_RenderText_Solid(font, text, color);
	auto texture = SDL_CreateTextureFromSurface(_sdlRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect textureRect;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.x = x;
	textureRect.y = y;

	SDL_RenderCopy(_sdlRenderer, texture, nullptr, &textureRect);

	SDL_DestroyTexture(texture);
}

void RenderController::DrawScreenRectangle(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderFillRect(_sdlRenderer, rect);
}

void RenderController::DrawScreenRectangleOutline(SDL_Rect* rect, int r, int g, int b, int a) const
{
	SDL_SetRenderDrawColor(_sdlRenderer, r, g, b, a);
	SDL_RenderDrawRect(_sdlRenderer, rect);
}
