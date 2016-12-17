#include "EntityController.h"
#include "Enemy.h"
#include "Entity.h"


EntityController::EntityController(RenderController* renderController, KeyboardController* keyboardController, 
									TextureController* textureController, int screenWidth, int screenHeight)
{
	_renderController = renderController;
	_textureController = textureController;
	_keyboardController = keyboardController;
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	_player = new Player(_renderController, _keyboardController,
		_textureController->GetTexture("resources/player.png"),
		_screenWidth / 2, _screenHeight / 2,
		_screenWidth, _screenHeight);
}

EntityController::~EntityController()
{
	delete _player;
	for (auto entity : _entities) { delete entity; }
}

void EntityController::AddEnemy(int spawnX, int spawnY)
{
	_newEntities.push(new Enemy(_renderController, this, _textureController->GetTexture("resources/skeleton.png"), spawnX, spawnY, _screenWidth, _screenHeight));
}

void EntityController::UpdateAll()
{
	_player->Update();
	for (auto entity : _entities) { entity->Update(); }

	while(!_newEntities.empty())
	{
		_entities.push_back(_newEntities.front());
		_newEntities.pop();
	}
}

void EntityController::RenderAll() const
{
	_player->Render();
//	for (auto entity : _entities) { entity->Render(); }
}

std::vector<Entity*> EntityController::FindInRange(int x, int y, int radius)
{
	std::vector<Entity*> entitiesInRange;
	for (auto entity : _entities)
	{
		auto entityPos = entity->GetPosition();
		auto xDiff = x - entityPos.first;
		auto yDiff = y - entityPos.second;
		auto distance = sqrt(xDiff*xDiff + yDiff*yDiff);

		if(distance <= radius)
		{
			entitiesInRange.push_back(entity);
		}
	}
	return entitiesInRange;
}

std::pair<int, int> EntityController::GetPlayerPosition() const
{
	return _player->GetPosition();
}
