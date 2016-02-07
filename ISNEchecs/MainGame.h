#pragma once
#include <SFML\Graphics.hpp>

#include "Graphics/GameObjectManager.h"

#include "Main/Board.h"


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

	Piece* _selectedPiece;
	bool _isAPieceSelected;
};

