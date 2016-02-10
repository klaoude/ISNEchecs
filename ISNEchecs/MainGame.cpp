#include <iostream>
#include <string>

#include "MainGame.h"
#include "Global.h"

#include "Main/CaseID.h"

#include "Server/Server.h"
#include "Server/Client.h"
#include "Server/MSClient.h"

MainGame::MainGame()
{

}

MainGame::~MainGame()
{
}

void MainGame::start()
{
	if (_gameState != Uninitialized)
		return;

	int choice;
	std::cout << "You are in debug mode" << std::endl;
	std::cout << "enter (1) if you want to debug server, (2) for debug board and (3) for debug graphics" << std::endl;
	std::cin >> choice;

	if (choice == 1)
	{
		std::cout << "Client (1), Server (2) or MasterServerClient(3) ? ";
		std::cin >> choice;

		if (choice == 2)
		{
			Server server;
			server.create();
		}
		else if (choice == 1)
		{
			sf::IpAddress ip = sf::IpAddress::getLocalAddress();
			Client client;
			client.connect(ip, 1337);
			client.send("hello");
		}
		else if (choice == 3)
		{
			sf::IpAddress ip = sf::IpAddress::getLocalAddress();
			MSClient client(ip, 4269);
			
			std::string username;
			std::string password;
			
			std::cout << "Username : ";
			std::cin.ignore();
			std::getline(std::cin, username);
			std::cout << "Password : ";
			//std::cin.ignore();
			std::getline(std::cin, password);


			std::cout << (char*)username.c_str() << " " << (char*)password.c_str() << std::endl;
			client.connect((char*)username.c_str(), (char*)password.c_str());
		
			std::string recv = client.recv();
			std::cout << recv << std::endl;
		}
	}
	else if (choice == 2)
	{
		std::cout << "Enter Case : ";
		std::cin >> choice;
		Board board(&_gameObjectManager);
		//board.getTyCo(choice);
		//board.getCase(choice).getPiece().move(&board, ID)

	}
	else if (choice == 3)
	{
		sf::Texture texture;
		texture.loadFromFile("Sprites/White_Queen.png");

		_sprite.setTexture(texture);
		_sprite.scale(2, 2);

		init();
		gameLoop();
	}
	else
	{
		init();
		gameLoop();
	}
}

void MainGame::init()
{
	_gameState = GameState::ShowingMenu;
	_window.create(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Chess");
	m_board = Board(&_gameObjectManager);
	_isAPieceSelected = false;
}

void MainGame::gameLoop()
{
	while (_window.isOpen())
	{
		switch (_gameState)
		{
		case GameState::ShowingMenu:
			showMenu();
			break;
		case GameState::Debugging:
			handleInput();
			draw();
			break;
		case GameState::Playing:
		case GameState::Joining:
			serverManager();
			handleInput();
			draw();
			break;
		case GameState::Exiting:
			_window.close();
			break;
		}		
	}
}

void MainGame::serverManager()
{
	if (!_client.isConnected())
	{
		switch (_gameState)
		{
		case GameState::Playing:
			_client.createServer();
			_isMyTurn = true;
		case GameState::Joining:
			_client.connect("127.0.0.1", 1337);
			_isMyTurn = false;
		default:
			return;
			break;
		}
	}
	if (!_isMyTurn)
	{
		_client.recv();
		_isMyTurn = true;
		std::cout << "whala" << std::endl;
	}
}

void MainGame::handleInput()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
			_window.close();
		if (event.type == sf::Event::MouseButtonPressed)
		{
#if _debugMode
			if (_isMyTurn)
			{
#endif			
				if (!_isAPieceSelected)
				{
					if (!m_board.getCase(event.mouseButton.x, event.mouseButton.y).isEmpty())
					{
						_selectedPiece = m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece();
						m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
						_isAPieceSelected = true;
					}
				}
				else
				{
					m_board.movePiece(_selectedPiece, m_board.getCase(event.mouseButton.x, event.mouseButton.y));
					_client.send("i move a piece");
					m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
					_isAPieceSelected = false;
					_isMyTurn = false;
				}
#if _debugMode
			}
#endif
		}
	}
}

void MainGame::draw()
{
	_window.clear();

	_gameObjectManager.draw(_window);

	_window.display();
}

void MainGame::showMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_window);
	switch (result)
	{
	case MainMenu::Exit:
		_gameState = Exiting;
		break;
	case MainMenu::Play:
		_gameState = Playing;
		break;
	case MainMenu::Join:
		_gameState = Joining;
		break;
	case MainMenu::Debug:
		_debugMode = true;
		_gameState = Debugging;
		break;
	}
}

sf::RenderWindow MainGame::_window;
GameObjectManager MainGame::_gameObjectManager;
MainGame::GameState MainGame::_gameState = Uninitialized;