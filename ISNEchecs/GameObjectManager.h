#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void add(std::string name, GameObject* gameObject);
	void remove(std::string name);

	void draw(sf::RenderWindow& window);

private:
	std::map<std::string, GameObject*> _gameObjects;
};

