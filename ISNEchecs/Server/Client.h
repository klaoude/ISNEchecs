#pragma once
#include <iostream>

#include <SFML/Network.hpp>

class Client
{
public:
	Client();
	~Client();

	sf::Packet recv();

	bool isConnected() const { return _connected; }

	void connect(sf::IpAddress ip, unsigned short port);
	void send(sf::Packet packet);
	void send(std::string);

	void createServer();
private:
	sf::TcpSocket _socket;

	sf::TcpListener _listener;

	bool _connected;
};

