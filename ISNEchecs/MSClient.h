#pragma once
#include <SFML\Network.hpp>
#include <JSON\JSON.h>

class MSClient
{
public:
	MSClient(sf::IpAddress ip, unsigned short port);
	~MSClient();

	void send(char* msg);
	void send(sf::Packet packet);

	void connect(char* username, char* password);

private:
	sf::UdpSocket _socket;
	sf::IpAddress _ipaddr;
	unsigned short _port;

	JSONObject _data;

	std::string _username;
	std::string _password;
};

