#include "RenderController.h"
#include <SDL2/SDL_ttf.h>


RenderController::RenderController(SDL_Renderer* renderer, TextureController* textureController, WorldPositionController* worldPositionController, int screenWidth, int screenHeight)
{
	_sdlRenderer = renderer;
	_textureController = textureController;
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

	RenderScreenTexture(texture, screenPos.first, screenPos.second);
}

void RenderController::RenderScreenTexture(RenderableSDLTexture* texture, int x, int y) const
{
	texture->TextureRect->x = x;
	texture->TextureRect->y = y;

	SDL_RenderCopy(_sdlRenderer, texture->RawTexture, nullptr, texture->TextureRect);
}

void RenderController::RenderScreenText(TTF_Font* font, const char* text, SDL_Color color, int x, int y) const
{
	// TODO: Do this properly
	// Wrap fonts in a custom model: could use RenderableSDLTexture
	// Create a font controller (same kind of idea as texture controller)
	auto surface = TTF_RenderText_Solid(font, text, color);
	auto texture = SDL_CreateTextureFromSurface(_sdlRenderer, surface);
	SDL_FreeSurface(surface);

	SDL_Rect textureRect;
	SDL_QueryTexture(texture, nullptr, nullptr, &textureRect.w, &textureRect.h);

	textureRect.x = x;
	textureRect.y = y;

	auto renderableTexture = new RenderableSDLTexture(texture, textureRect.w, textureRect.h);

	RenderScreenTexture(renderableTexture, x, y);

//	delete renderableTexture; // Make sure to do this when this is properly implemented
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
