#pragma once
#include "FontController.h"
#include "RenderController.h"
#include "SDL2/SDL_ttf.h"

class HUDController
{
public:
	HUDController(FontController* fontController, RenderController* renderController);
	~HUDController();

	void Initialise();
	void Render() const;

private:
	FontController* _fontController;
	RenderController* _renderController;

	SDL_Color _hudFontColor;
	TTF_Font* _hudFont;
};

