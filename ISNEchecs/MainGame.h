#pragma once
#include <thread>

#include <SFML\Graphics.hpp>

#include "Graphics/GameObjectManager.h"
#include "Graphics/MainMenu.h"

#include "Main/Board.h"

#include "Server\Client.h"
#include "AI.h"

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
	void enableSurbrillance(Piece piece, std::vector<int> path);
	void disableSurbrillance();	

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

	std::thread _thread;
	std::map<Piece*, std::vector<int>> _allPath;
	bool _stop;
};

