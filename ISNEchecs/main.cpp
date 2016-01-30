#include <iostream>

#include "MainGame.h"
#include "Server.h"
#include "Client.h"

int main(int argc, char** argv)
{
	int choice;
	std::cout << "You are in debug mode" << std::endl;
	std::cout << "enter (1) if you want to debug server" << std::endl;
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
			Client client;
			client.connect("192.168.0.151", 1337);
		}
	}
	else 
	{
		MainGame game;
		game.start();
	}

	system("Pause");

	return 0;
}