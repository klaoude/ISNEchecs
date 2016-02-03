#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	void connect(sf::IpAddress ip, unsigned short port);
	void send(char* msg);
private:
	sf::TcpSocket _socket;
};

