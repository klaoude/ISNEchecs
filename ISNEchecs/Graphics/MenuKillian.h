#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>
#include "MenuManager.h"

class MenuKillian
{
public:
	MenuKillian();
	void init(sf::RenderWindow& window);
	MENUS recevoirCoord(int x, int y);
};