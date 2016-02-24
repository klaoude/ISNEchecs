#include "../Server/Client.h"

Client::Client()
{
	_connected = false;
}

Client::~Client()
{

}

sf::Packet Client::recv()
{
	sf::Packet packet;
	if (_socket.receive(packet) == sf::Socket::NotReady)
		packet << -1;
	return packet;
}

void Client::send(sf::Packet packet)
{
	_socket.send(packet);
	std::cout << "i send : " << packet << std::endl;
}

void Client::send(std::string msg)
{
	sf::Packet packet;
	packet << msg;
	_socket.send(packet);
	std::cout << "i send : " << msg << std::endl;
}

void Client::connect(sf::IpAddress ip, unsigned short port)
{
	_socket.connect(ip, port);
	std::cout << "connected to " << ip << std::endl;
	_connected = true;
	_socket.setBlocking(false);
}

void Client::createServer()
{
	std::cout << "i'm waiting for someone to connect" << std::endl;
	_listener.listen(4269);
	_listener.accept(_socket);
	_socket.setBlocking(false);

	std::cout << "client connected" << std::endl;
	_connected = true;	
}