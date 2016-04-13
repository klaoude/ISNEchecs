#include "../Graphics/GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::addSurbrillance(std::string name, GameObject* gameObject)
{
	_surbrillance.emplace(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::removeSurbrillance(std::string name)
{
	std::map<std::string, GameObject*>::iterator result = _surbrillance.find(name);
	if (result != _surbrillance.end())
	{
		delete result->second;
		_surbrillance.erase(result);
	}
}

void GameObjectManager::add(std::string name, GameObject* gameObject)
{
	_gameObjects.emplace(std::pair<std::string, GameObject*>(name, gameObject));
}

void GameObjectManager::remove(std::string name)
{
	std::unordered_map<std::string, GameObject*>::iterator result = _gameObjects.find(name);
	if (result != _gameObjects.end())
	{
		delete result->second;
		_gameObjects.erase(result);
	}
}

GameObject* GameObjectManager::get(std::string name)
{
	std::unordered_map<std::string, GameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return nullptr;
	return results->second;
}

void GameObjectManager::replace(std::string name, GameObject* gameObject)
{
	for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (i->first == name)
			i->second = gameObject;
	}
}

void GameObjectManager::draw(sf::RenderWindow& window)
{
	_background->draw(window);
	
	for (auto i = _surbrillance.begin(); i != _surbrillance.end(); i++)
		i->second->draw(window);

	for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		i->second->draw(window);
	}
}

void GameObjectManager::fix()
{
	std::unordered_map<std::string, GameObject*> test;
	for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (i->first == "Board")
			test.emplace(std::pair<std::string, GameObject*>(i->first, i->second));
	}
	for (auto i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (i->first != "Board")
			test.emplace(std::pair<std::string, GameObject*>(i->first, i->second));
	}
	_gameObjects = test;
}