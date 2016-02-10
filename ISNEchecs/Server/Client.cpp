#include "../Server/Client.h"

Client::Client()
{
	_connected = false;
}

Client::~Client()
{

}

void Client::recv()
{
	_socket.receive(_buffer, sizeof(_buffer), _received);
	std::cout << "recv : " << _received << std::endl;
}

void Client::send(char* msg)
{
	_socket.send(msg, strlen(msg));
	std::cout << "i send : " << msg << std::endl;
}

void Client::connect(sf::IpAddress ip, unsigned short port)
{
	_socket.connect(ip, port);
	std::cout << "connected to " << ip << std::endl;
	_connected = true;
}

void Client::createServer()
{
	std::cout << "i'm waiting for someone to connect" << std::endl;
	_listener.listen(1337);
	_listener.accept(_socket);

	std::cout << "client connected" << std::endl;
	_connected = true;	
}