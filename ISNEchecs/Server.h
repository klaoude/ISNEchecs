#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Server
{
public:
	Server();
	~Server();

	void create();
private:
	sf::TcpListener _listener;
	sf::TcpSocket _client;
	unsigned short _port = 1337;
};