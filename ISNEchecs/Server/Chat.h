#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class Chat
{
public:
	Chat();
	~Chat();

	void init();
	void update(char character);
	void draw(sf::RenderWindow& window);

	void send(std::string msg);
	void recv();
private:
	std::vector<sf::Text> m_chatBuffer;
	std::string m_currentMsg;

	sf::Font m_font;
};

