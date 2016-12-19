#include "HUDController.h"

HUDController::HUDController(FontController* fontController, RenderController* renderController)
{
	_fontController = fontController;
	_renderController = renderController;

	_hudFontColor = {255, 255, 255, 255};
	_hudFont = nullptr;
}

HUDController::~HUDController()
{
	TTF_CloseFont(_hudFont);
}

void HUDController::Initialise()
{
	_hudFont = _fontController->GetFont("resources/arial.ttf", 24);
}

void HUDController::Render() const
{
	_renderController->RenderScreenText(_hudFont, "HUD", _hudFontColor, 0, 0);
}
