#pragma once

#include <SFML\Network.hpp>

class MSClient
{
public:
	MSClient(sf::IpAddress ip, unsigned short port);
	~MSClient();

	void send(char* msg);

private:
	sf::UdpSocket _socket;
	sf::IpAddress _ipaddr;
	unsigned short _port;
};

