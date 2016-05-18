#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "MenuKillian.h"

class Lan
{
public:
	Lan();
	void init(sf::RenderWindow& window);
	MENUS recevoirCoord(int x, int y);
};