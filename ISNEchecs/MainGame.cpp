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
	_window.create(sf::VideoMode(SCREEN_HEIGHT, SCREEN_WIDTH), "Chess");
	m_board = Board(&_gameObjectManager);
	_isAPieceSelected = false;
}

void MainGame::gameLoop()
{
	while (_window.isOpen())
	{
		handleInput();		

		draw();
	}
}

void MainGame::handleInput()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		if (event.type == sf::Event::EventType::Closed)
			_window.close();
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				std::cout << "space bar press" << std::endl;
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			//m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
			if (!_isAPieceSelected && !m_board.getCase(event.mouseButton.x, event.mouseButton.y).isEmpty())
			{
				_selectedPiece = m_board.getCase(event.mouseButton.x, event.mouseButton.y).getPiece();
				m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
				_isAPieceSelected = true;
			}				
			else
			{
				m_board.movePiece(_selectedPiece, m_board.getCase(event.mouseButton.x, event.mouseButton.y));
				m_board.getCase(event.mouseButton.x, event.mouseButton.y).debugCase();
				_isAPieceSelected = false;
			}
		}
	}
}

void MainGame::draw()
{
	_window.clear();

	//_window.draw(_sprite);
	_gameObjectManager.draw(_window);

	_window.display();
}

sf::RenderWindow MainGame::_window;
GameObjectManager MainGame::_gameObjectManager;