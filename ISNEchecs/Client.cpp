#include "Client.h"

Client::Client()
{

}

Client::~Client()
{

}

void Client::connect(std::string ip, int port)
{
	if (_socket.connect(ip, port) != sf::Socket::Done)
		std::cout << "ERROR 0" << std::endl;

	sf::Packet msg;
	msg << "coucou";
	if (_socket.send(msg) != sf::Socket::Done)
		std::cout << "ERROR 1" << std::endl;
}