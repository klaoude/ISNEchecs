#include "MSClient.h"

MSClient::MSClient()
{
}

MSClient::~MSClient()
{
}

void MSClient::connect(sf::IpAddress ip, unsigned short port)
{
	sf::Packet packet;
	std::string msg = "coucou";


	packet.append(msg.c_str(), sizeof(msg));
	_socket.send(packet, ip, 4269);
}
