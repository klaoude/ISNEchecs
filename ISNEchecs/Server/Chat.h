#pragma once
#include <vector>
#include <SFML\Graphics.hpp>

class GameObjectManager;

class Chat
{
public:
	Chat();
	~Chat();

	void init(GameObjectManager& gom);
	void update(char character);
	void pop();
	void draw(sf::RenderWindow& window);

	void send();
	void recv();
private:
	std::vector<sf::Text> m_chatBuffer;
	std::string m_currentMsg;

	sf::Font m_font;
};

