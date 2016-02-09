#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	void recv();

	bool isConnected() { return _connected; }

	void connect(sf::IpAddress ip, unsigned short port);
	void send(char* msg);

	void createServer();
private:
	sf::TcpSocket _socket;

	sf::TcpListener _listener;

	char _buffer[2000];
	std::size_t _received;

	bool _connected;
};

