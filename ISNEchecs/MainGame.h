#pragma once
#include <SFML\Graphics.hpp>

#include "Graphics/GameObjectManager.h"

#include "Main/Board.h"

#include "Server\Client.h"
#include "AI.h"
#include "Server\Chat.h"

class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	void init();
	void initAI();
	void gameLoop();

	void serverManager();
	void handleInput();
	void draw();
	void showMenu();

	void enableSurbrillance(Piece piece);
	void disableSurbrillance();
	void disableSurbrillance(int id);


	enum GameState { Uninitialized, ShowingMenu, Playing, Exiting, Joining, Debugging, VersusIA };
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

	Couleur _clientColor;

	std::string _ipaddress;

	std::vector<std::string> _surbrillance;

	AI _ai;

	Chat m_chat;
};

