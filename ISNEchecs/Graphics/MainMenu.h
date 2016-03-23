#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <list>
#include <iostream>

class MainMenu
{
public:
	enum MenuResult { Nothing, Exit, Play, Join, Debug };

	struct MenuItem
	{
	public:
		sf::Rect<int> rect;
		MenuResult action;
	};
	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);

	std::list<MenuItem> _menuItems;
};
