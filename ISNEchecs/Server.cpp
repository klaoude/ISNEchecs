#include "Server.h"

Server::Server()
{

}

Server::~Server()
{

}

void Server::create()
{
	_listener.listen(1337);
	_listener.accept(_client);

	_client.receive(_buffer, sizeof(_buffer), _received);

	std::cout << _buffer << std::endl;
}