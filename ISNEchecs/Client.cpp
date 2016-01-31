#include "Client.h"

Client::Client()
{

}

Client::~Client()
{

}

void Client::send(char* msg)
{
	_socket.send(msg, strlen(msg));
}

void Client::connect(sf::IpAddress ip, unsigned short port)
{
	_socket.connect(ip, port);	
}