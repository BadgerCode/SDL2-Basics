#pragma once

#include "KeyboardController.h"
#include "RenderController.h"
#include "RenderableSDLTexture.h"
#include "Entity.h"
#include "LightSource.h"

struct PlayerMovement
{
	bool Up;
	bool Down;
	bool Left;
	bool Right;
};

class Player : public Entity
{
public:
	Player(RenderController* renderController, KeyboardController* keyboardController, 
			RenderableSDLTexture* playerTexture, LightSource* playerLight);
	~Player();

	void Render() const override;
	void Update() override;
	std::pair<int, int> GetPosition() const override;
	void SetPosition(int worldX, int worldY) override;
private:
	RenderController* _renderController;
	KeyboardController* _keyboardController;

	RenderableSDLTexture* _playerTexture;
	LightSource* _playerLight;

	int _width;
	int _height;
	int _worldX;
	int _worldY;
};

