#pragma once
#include "../Graphics/GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	int getObjectCount() const { return _gameObjects.size(); }
	std::map<std::string, GameObject*> getMap() { return _gameObjects; }

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);	
	GameObject* get(std::string name);

	void draw(sf::RenderWindow& _window);

private:
	std::map<std::string, GameObject*> _gameObjects;
};

