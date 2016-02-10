#pragma once
#include <SFML\Graphics.hpp>

#include "Graphics/GameObjectManager.h"
#include "Graphics/MainMenu.h"

#include "Main/Board.h"

#include "Server\Client.h"


class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	void init();
	void gameLoop();

	void serverManager();
	void handleInput();
	void draw();
	void showMenu();

	enum GameState { Uninitialized, ShowingMenu, Playing, Exiting, Joining, Debugging };
	static GameState _gameState;

	static sf::RenderWindow _window;

	Client _client;

	std::string _windowTitle = "Chess";

	static GameObjectManager _gameObjectManager;

	sf::Sprite _sprite;

	Board m_board;
	bool _debugMode;

	Piece* _selectedPiece;
	bool _isAPieceSelected;
	bool _isMyTurn;
};

