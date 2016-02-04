#pragma once
#include <SFML\Graphics.hpp>

#include "Board.h"
#include "GameObjectManager.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	void init();
	void gameLoop();

	void handleInput();
	void draw();

	Board board;

	sf::RenderWindow _window;
	int _screenWidth;
	int _screenHeight;

	std::string _windowTitle = "Chess";

	static GameObjectManager _gameObjectManager;
};

