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

	static sf::RenderWindow _window;

	std::string _windowTitle = "Chess";

	static GameObjectManager _gameObjectManager;

	sf::Sprite _sprite;

	Board m_board;
};

