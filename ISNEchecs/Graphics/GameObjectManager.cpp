#include "../Graphics/GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::add(std::string name, GameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::map<std::string, GameObject*>::iterator result = _gameObjects.find(name);
	if (result != _gameObjects.end())
	{
		delete result->second;
		_gameObjects.erase(result);
	}
}

GameObject* GameObjectManager::get(std::string name)
{
	std::map<std::string, GameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;
}


void GameObjectManager::draw(sf::RenderWindow& window)
{
	std::map<std::string, GameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->draw(window);
		itr++;
	}
}