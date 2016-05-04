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
	void send(std::string str);

	void createServer();
private:
	sf::TcpSocket m_socket;

	sf::TcpListener _listener;

	bool _connected;
};

