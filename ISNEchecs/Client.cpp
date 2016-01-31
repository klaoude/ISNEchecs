#include "Client.h"

Client::Client()
{

}

Client::~Client()
{

}

void Client::connect(sf::IpAddress ip, unsigned short port)
{
	_socket.connect(ip, port);

	std::string msg = "coucou";
	_socket.send(msg.c_str(), msg.length() + 1);
}