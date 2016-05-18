#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "MenuKillian.h"

class Solo
{
public:
	Solo();
	void init(sf::RenderWindow& window);
	MENUS recevoirCoord(int x, int y);
};