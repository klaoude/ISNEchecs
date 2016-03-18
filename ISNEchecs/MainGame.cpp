#pragma once
#include <iostream>
#include <string>

#include "MainGame.h"
#include "Global.h"

#include "Main/CaseID.h"

#include "Server/Server.h"
#include "Server/Client.h"
#include "Server/MSClient.h"

#include "Fonctions.h"
#include "canMove.h"
#include "Son.h"

void debug(std::string debugstring)
{
	std::cout << "[DEBUG] " << debugstring << std::endl;
}

void MainGame::enableSurbrillance(Piece piece)
{
	auto allPath = getAllPath(&m_board, &piece, m_board.getMasterColor());
	for (int i = 0; i < allPath.size(); i++)
	{
		if (m_board.getCase(allPath[i]).getPiece()->getColor() != piece.getColor())
		{
			GameObject* go = new GameObject("Sprites/surbrillance.png");
			go->setPosition(m_board.getCase(allPath[i]).getPos());
			go->setColor(sf::Color(255, 255, 255, 100));
			setScale(go, 2);
			_gameObjectManager.addSurbrillance("Surbrillance" + std::to_string(i), go);
			_surbrillance.push_back("Surbrillance" + std::to_string(i));
		}		
	}
}

void MainGame::disableSurbrillance()
{
	for (int i = 0; i < _surbrillance.size(); i++)
	{
		_gameObjectManager.removeSurbrillance(_surbrillance[i]);
	}
	_surbrillance.clear();
}

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
			sf::IpAddress ip = "90.9.126.153";
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
			client.coutRecv();

			client.find();
			client.coutRecv();

			client.coutRecv();

			client.coutRecv();

			std::string receive = client.recv();
			if (receive == "create")
			{
				init();
				_gameState = Playing;
				gameLoop();
			}
			else if (receive == "join")
			{
				init();
				_ipaddress = "127.0.0.1";
				_gameState = Joining;
				gameLoop();
			}

			system("Pause");
		}
	}
	else if (choice == 2)
	{
		init();
		initAI();
		_gameState = VersusIA;
		gameLoop();
		system("Pause");
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

void MainGame::initAI()
{
	m_board = Board(&_gameObjectManager, NOIR);
	_ai = AI(&m_board);
	_isMyTurn = true;
}

void MainGame::init()
{
	_ipaddress = "127.0.0.1";
	_gameState = GameState::ShowingMenu;
	_window.create(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Chess");
	_isAPieceSelected = false;
	_debugMode = false;
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
		case GameState::VersusIA:
			if (!_isMyTurn)
			{
				_ai.play();
				_isMyTurn = true;
			}
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
	if (!_isMyTurn)
	{
		int add = 0;
		if (_clientColor == BLANC)
			add = 63;
		sf::Packet packet = _client.recv();
		int pieceID, caseID;
		packet >> pieceID >> caseID;
		if (pieceID != -1)
		{
			m_board.movePiece(m_board.getCase(abs(add - pieceID)).getPiece(), m_board.getCase(abs(add - caseID)));
			_isMyTurn = true;
			debug("is my turn");
		}
		
	}
	if (!_client.isConnected())
	{
		std::string ip;
		switch (_gameState)
		{
		case GameState::Playing:
			_client.createServer();
			_isMyTurn = true;
			_clientColor = BLANC;
			m_board = Board(&_gameObjectManager, _clientColor);
			break;
		case GameState::Joining:			
			std::cout << "IP : ";
			std::cin >> ip;
			_client.connect(ip, 1337);
			_isMyTurn = false;
			_clientColor = NOIR;
			m_board = Board(&_gameObjectManager, _clientColor);
			break;
		default:
			return;
			break;
		}
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
			if (_gameState == VersusIA)
			{
				if (_isMyTurn)
				{
					if (!_isAPieceSelected)
					{
						if (!m_board.getCase(event.mouseButton.x, event.mouseButton.y).isEmpty())
						{
							if (m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece()->getColor() != _clientColor)
							{
								_selectedPiece = m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece();
								//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
								if (_selectedPiece != new Piece())
									enableSurbrillance(*_selectedPiece);
								_isAPieceSelected = true;
							}
						}
					}
					else
					{
						int oldPieceID = _selectedPiece->getID();
						if (m_board.movePiece(_selectedPiece, m_board.getCase(event.mouseButton.x, event.mouseButton.y)))
						{
							_selectedPiece = new Piece();
							disableSurbrillance();
							_isAPieceSelected = false;
							_isMyTurn = false;
							std::cout << "echec:" << echec(&m_board) << std::endl;
							std::cout << "echecmat:" << echecm(&m_board) << std::endl;
							std::cout << "-----Fin du tour-----" << std::endl;
						}
						else
						{
							_selectedPiece = new Piece();
							disableSurbrillance();
							_isAPieceSelected = false;
						}
					}
				}
			}
			else
			{
				if (!_debugMode)
				{
					if (_isMyTurn)
					{
						if (!_isAPieceSelected)
						{
							if (!m_board.getCase(event.mouseButton.x, event.mouseButton.y).isEmpty())
							{
								if (m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece()->getColor() == _clientColor)
								{
									_selectedPiece = m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece();
									//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
									enableSurbrillance(*_selectedPiece);
									_isAPieceSelected = true;
								}
							}
						}
						else
						{
							int oldPieceID = _selectedPiece->getID();
							if (m_board.movePiece(_selectedPiece, m_board.getCase(event.mouseButton.x, event.mouseButton.y)))
							{
								int add = 0;
								if (_clientColor == BLANC)
									add = 63;
								sf::Packet packet;
								packet << abs(add - oldPieceID);
								packet << abs(add - m_board.getCase(event.mouseButton.x, event.mouseButton.y).getID());
								_client.send(packet);
								//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
								_isAPieceSelected = false;
								_isMyTurn = false;
								debug("is not my turn");
								_selectedPiece = new Piece();
								disableSurbrillance();
								std::cout << "echec:" << echec(&m_board) << std::endl;
								std::cout << "echecmat:" << echecm(&m_board) << std::endl;
								std::cout << "-----Fin du tour-----" << std::endl;
							}
							else
							{
								_selectedPiece = new Piece();
								_isAPieceSelected = false;
								disableSurbrillance();
							}
						}
					}
				}
				else
				{
					if (!_isAPieceSelected)
					{
						if (!m_board.getCase(event.mouseButton.x, event.mouseButton.y).isEmpty())
						{
							if (m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece()->getColor() != _clientColor)
							{
								_selectedPiece = m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece();
								//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
								if (_selectedPiece != new Piece())
									enableSurbrillance(*_selectedPiece);
								_isAPieceSelected = true;
							}
						}
					}
					else
					{
						int oldPieceID = _selectedPiece->getID();						
						if (m_board.movePiece(_selectedPiece, m_board.getCase(event.mouseButton.x, event.mouseButton.y)))
						{
							std::cout << "echec:" << echec(&m_board) << std::endl;
							std::cout << "echecmat:" << echecm(&m_board) << std::endl;
							std::cout << "-----Fin du tour-----" << std::endl;
							int add = 0;
							if (m_board.getMasterColor() == BLANC)
								add = 63;
							sf::Packet packet;
							packet << abs(add - oldPieceID);
							packet << abs(add - m_board.getCase(event.mouseButton.x, event.mouseButton.y).getID());
							_client.send(packet);
							//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();

							_selectedPiece = new Piece();
							disableSurbrillance();
							_isAPieceSelected = false;
						}
						else
						{
							_selectedPiece = new Piece();

							disableSurbrillance();
							_isAPieceSelected = false;
						}
					}
				}
			}			
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
		m_board = Board(&_gameObjectManager, NOIR);
		break;
	}
}

sf::RenderWindow MainGame::_window;
GameObjectManager MainGame::_gameObjectManager;
MainGame::GameState MainGame::_gameState = Uninitialized;