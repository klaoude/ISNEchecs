#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "MenuKillian.h"

class Options
{
public:
	Options();
	void init(sf::RenderWindow& window);
	void goMenu();
	MENUS recevoirCoord(int x, int y);
};