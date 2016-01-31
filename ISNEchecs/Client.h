#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	void connect(sf::IpAddress ip, unsigned short port);
private:
	sf::TcpSocket _socket;
};

