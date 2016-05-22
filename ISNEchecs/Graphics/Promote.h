#pragma once

#include "../Global.h"
#include "../Main/PieceInfo.h"
#include "GameObjectManager.h"

class Promote
{
public:
	Promote();
	void init(GameObjectManager& gom, Couleur color);
	Type getPromote(sf::RenderWindow& window);
	void remove();

private:
	int m_x = 0;
	int m_y = 0;
	int m_w = 0;
	int m_h = 0;
	bool m_show = false;
};