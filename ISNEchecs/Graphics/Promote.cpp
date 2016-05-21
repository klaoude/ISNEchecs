#include "Promote.h"

Promote::Promote()
{}

void Promote::init(GameObjectManager& gom, Couleur color)
{
	if (!m_show)
	{
		gom.add("Promote", new GameObject((color == BLANC ? "Sprites/PromoteWhite.png" : "Sprites/PromoteBlack.png")));
		gom.get("Promote")->scale(BOARD_SIZE / (4/3.0f) / 300.0f, BOARD_SIZE / 4.0f / 100.0f);	
		m_x = BOARD_SIZE / 2.0f - gom.get("Promote")->getTextureSize().x / 2.0f;
		m_y = BOARD_SIZE / 2.0f - gom.get("Promote")->getTextureSize().y / 2.0f;
		gom.get("Promote")->setPosition(m_x, m_y);
		m_h = gom.get("Promote")->getSprite().getTextureRect().height;
		m_w = gom.get("Promote")->getSprite().getTextureRect().width;
		m_show = true;
	}
	
}

Type Promote::getPromote(sf::RenderWindow& window)
{
	sf::Event evnt;
	while (window.pollEvent(evnt))
	{
		if (evnt.type == sf::Event::MouseButtonPressed)
		{
			int x = evnt.mouseButton.x;
			int y = evnt.mouseButton.y;

			printf("test");

			if (x > m_x + (0 * m_h) / 5 && x < m_x + (1 * m_h) / 5 && y > m_y && y < m_y + m_w)
				return PION;
			if (x > m_x + (1 * m_h) / 5 && x < m_x + (2 * m_h) / 5 && y > m_y && y < m_y + m_w)
				return CAVALIER;
			if (x > m_x + (2 * m_h) / 5 && x < m_x + (3 * m_h) / 5 && y > m_y && y < m_y + m_w)
				return FOU;
			if (x > m_x + (3 * m_h) / 5 && x < m_x + (4 * m_h) / 5 && y > m_y && y < m_y + m_w)
				return TOUR;
			if (x > m_x + (4 * m_h) / 5 && x < m_x + (5 * m_h) / 5 && y > m_y && y < m_y + m_w)
				return REINE;
		}
	}
}

void Promote::remove()
{
	m_show = false;
}