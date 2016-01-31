#pragma once

#include <SFML\Network.hpp>

class MSClient
{
public:
	MSClient();
	~MSClient();

	void connect(sf::IpAddress ip, unsigned short port);

private:
	sf::UdpSocket _socket;
};

