#include <iostream>

#include "MainGame.h"
#include "Server.h"
#include "Client.h"

int main(int argc, char** argv)
{
	int choice;
	std::cout << "You are in debug mode" << std::endl;
	std::cout << "enter (1) if you want to debug server, (2) for debug board and (3) for debug graphics" << std::endl;
	std::cin >> choice;

	if (choice == 1) 
	{
		std::cout << "Client (1) or Server (2) ? ";
		std::cin >> choice;

		if (choice == 2)
		{
			Server server;
			server.create();
		}
		else
		{
			sf::IpAddress ip = sf::IpAddress::getLocalAddress();
			Client client;
			client.connect(ip, 1337);
		}
	}

	else if (choice == 2)
	{
		std::cout << "Enter Case : ";
		std::cin >> choice;
		Board board;
		board.getPiece(choice);
	}

	else 
	{
		MainGame game;
		game.start();
	}

	system("Pause");

	return 0;
}