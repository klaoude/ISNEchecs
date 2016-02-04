#include <iostream>

#include "MainGame.h"
#include "CaseID.h"
#include "Server.h"
#include "Client.h"
#include "MSClient.h"

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
			client.connect("klaoude", "test");
		}
	}
	else if (choice == 2)
	{
		std::cout << "Enter Case : ";
		std::cin >> choice;
		Board board;
		//board.getTyCo(choice);
		//board.getCase(choice).getPiece().move(&board, ID)

	}
	else if (choice == 3)
	{
		
	}
	else
	{
		init();
		gameLoop();
	}
}

void MainGame::init()
{
	_window.create(sf::VideoMode(800, 800), "Chess");
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


	while (_window.pollEvent(event)){
		if (event.type == sf::Event::EventType::Closed)
			_window.close();
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				std::cout << "space bar press" << std::endl;
			}
		}
	}
}

void MainGame::draw()
{
	_window.clear();

	_window.display();
}