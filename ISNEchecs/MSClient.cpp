#include "MSClient.h"

MSClient::MSClient(sf::IpAddress ip, unsigned short port)
{
	_ipaddr = ip;
	_port = port;
}

MSClient::~MSClient()
{
}

void MSClient::send(char* msg)
{
	sf::Packet packet;
	packet.append(msg, strlen(msg));

	_socket.send(packet, _ipaddr, _port);
}
