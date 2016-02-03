#include "MSClient.h"

MSClient::MSClient(sf::IpAddress ip, unsigned short port)
{
	_ipaddr = ip;
	_port = port;
}

MSClient::~MSClient()
{
}

void MSClient::send(char* msg)
{
	sf::Packet packet;
	packet.append(msg, strlen(msg));

	_socket.send(packet, _ipaddr, _port);
}

void MSClient::send(sf::Packet packet)
{
	_socket.send(packet, _ipaddr, _port);
}

void MSClient::connect(char* username, char* password)
{
	_username = username;
	_password = password;

	_data[L"Action"] = new JSONValue(L"connect");
	_data[L"Username"] = new JSONValue(std::wstring(username, username + strlen(username)));
	_data[L"Password"] = new JSONValue(std::wstring(password, password + strlen(password)));

	JSONValue *val = new JSONValue(_data);
	_data.clear();

	std::wstring dataString = val->Stringify();
	delete val;

	std::string packetData;
	packetData.assign(dataString.begin(), dataString.end());

	sf::Packet packet;
	packet.append(packetData.c_str(), packetData.length());

	send(packet);
}
