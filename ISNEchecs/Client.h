#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	void connect(std::string ip, int port);
private:
	sf::TcpSocket _socket;
};

