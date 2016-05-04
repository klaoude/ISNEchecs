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
	if (m_socket.receive(packet) == sf::Socket::NotReady)
		packet << -1;
	return packet;
}

void Client::send(sf::Packet packet)
{
	m_socket.send(packet);
}

void Client::send(std::string msg)
{
	sf::Packet packet;
	packet << 2;
	packet << msg;
	m_socket.send(packet);
	std::cout << "send string " << msg << std::endl;
}

void Client::connect(sf::IpAddress ip, unsigned short port)
{
	m_socket.connect(ip, port);
	std::cout << "connected to " << ip << std::endl;
	_connected = true;
	m_socket.setBlocking(false);
}

void Client::createServer()
{
	std::cout << "i'm waiting for someone to connect" << std::endl;
	_listener.listen(1337);
	_listener.accept(m_socket);
	m_socket.setBlocking(false);

	std::cout << "client connected" << std::endl;
	_connected = true;	
}