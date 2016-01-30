#include "Server.h"

Server::Server()
{

}

Server::~Server()
{

}

void Server::create()
{
	if (_listener.listen(_port) != sf::Socket::Done)
		std::cout << "ERROR 0" << std::endl;

	if (_listener.accept(_client) != sf::Socket::Done)
		std::cout << "ERROR 1" << std::endl;

	sf::Packet recv;
	if (_client.receive(recv) != sf::Socket::Done)
		std::cout << "ERROR 2" << std::endl;
	std::string msg;
	recv >> msg;

	std::cout << msg << std::endl;
}