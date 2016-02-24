#include "../Server/MSClient.h"
#include <iostream>

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

void MSClient::sendData()
{
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

void MSClient::connect(char* username, char* password)
{
	_username = username;
	_password = password;

	_data[L"Action"] = new JSONValue(L"connect");
	_data[L"Username"] = new JSONValue(std::wstring(username, username + strlen(username)));
	_data[L"Password"] = new JSONValue(std::wstring(password, password + strlen(password)));

	sendData();
}

void MSClient::find()
{
	const char* username = _username.c_str();
	_data[L"Action"] = new JSONValue(L"find");
	_data[L"Username"] = new JSONValue(std::wstring(username, username + strlen(username)));

	sendData();
}

std::string MSClient::recv()
{
	char buffer[512];
	sf::IpAddress ipAddr;
	size_t recvSize;

	_socket.receive(buffer, 512, recvSize, ipAddr, _port);

	std::string recvString(buffer, recvSize);
	return recvString;
}

void MSClient::coutRecv()
{
	std::string recv = this->recv();
	std::cout << recv << std::endl;
}