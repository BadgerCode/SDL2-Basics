#pragma once
#include "RenderableSDLTexture.h"
#include <utility>

class LightSource
{
public:
	LightSource(RenderableSDLTexture* texture, int worldX, int worldY);
	~LightSource();

	RenderableSDLTexture* Texture;
	void SetWorldPosition(int worldX, int worldY);
	std::pair<int, int> GetWorldPosition() const;
private:
	int _worldX;
	int _worldY;
};

