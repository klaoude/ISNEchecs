#pragma once
#include <SFML\Network.hpp>

#include "../Server/JSON.h"

class MSClient
{
public:
	MSClient(sf::IpAddress ip, unsigned short port);
	~MSClient();

	void send(char* msg);
	void send(sf::Packet packet);
	void sendData();

	void connect(char* username, char* password);
	void find();

	std::string recv();
	void coutRecv();

private:
	sf::UdpSocket _socket;
	sf::IpAddress _ipaddr;
	unsigned short _port;

	JSONObject _data;

	std::string _username;
	std::string _password;
};

