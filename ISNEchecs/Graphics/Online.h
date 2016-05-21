#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "MenuKillian.h"

class Online
{
public:
	Online();
	void init(sf::RenderWindow& window);
	MENUS recevoirCoord(int x, int y);
};