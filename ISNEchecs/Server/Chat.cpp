#include "Chat.h"
#include "../Global.h"
#include "../Graphics/GameObjectManager.h"
#include <iostream>

Chat::Chat()
{

}

Chat::~Chat()
{
}

void Chat::init(GameObjectManager& gom)
{
	gom.add("Chat", new GameObject("Sprites/Chat.png"));
	gom.get("Chat")->setPosition(0, 400);
	m_font.loadFromFile("Font/CSMS.ttf");
}

void Chat::update(char character)
{
	m_currentMsg += character;
}

void Chat::pop()
{
	if(m_currentMsg.size() > 0)
		m_currentMsg.pop_back();
}

void Chat::send()
{
	if (m_chatBuffer.size() >= 4)
		m_chatBuffer.erase(m_chatBuffer.begin());	

	sf::Text text;
	text.setString(m_currentMsg);
	m_chatBuffer.push_back(text);
	m_currentMsg.clear();
}

void Chat::recv(sf::String msg)
{
	sf::Text text;
	text.setString(msg);
	text.setColor(sf::Color::Black);
	m_chatBuffer.push_back(text);
}

void Chat::draw(sf::RenderWindow& window)
{
	for(int i = 0; i < m_chatBuffer.size(); i++)
	{
		m_chatBuffer[i].setPosition(0, 480 - (4-i)*20);
		m_chatBuffer[i].setFont(m_font);
		m_chatBuffer[i].setCharacterSize(14);
		
		window.draw(m_chatBuffer[i]);
	}

	sf::Text text;
	text.setFont(m_font);
	text.setCharacterSize(10);
	text.setColor(sf::Color::Black);
	text.setString(m_currentMsg);
	text.setPosition(4, 480);
	
	window.draw(text);
}

void Chat::clear()
{
	m_currentMsg.clear();
}
