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

	char _buffer[2000];
	std::size_t _received;
};