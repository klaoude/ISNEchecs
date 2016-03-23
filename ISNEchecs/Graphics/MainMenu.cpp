#include "MainMenu.h"
#include "../Global.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("sprites/MainMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);
	
	MenuItem debugButton;
	debugButton.rect.top = 120 * MAINMENU_SCALE;
	debugButton.rect.height = 238 * MAINMENU_SCALE;
	debugButton.rect.left = 340 * MAINMENU_SCALE;
	debugButton.rect.width = 600 * MAINMENU_SCALE;
	debugButton.action = Debug;

	MenuItem playButton;
	playButton.rect.top = 300 * MAINMENU_SCALE;
	playButton.rect.height = 330 * MAINMENU_SCALE;
	playButton.rect.left = 340 * MAINMENU_SCALE;
	playButton.rect.width = 500 * MAINMENU_SCALE;
	playButton.action = Play;

	MenuItem joinButton;
	joinButton.rect.top = 370 * MAINMENU_SCALE;
	joinButton.rect.height = 400 * MAINMENU_SCALE;
	joinButton.rect.left = 373 * MAINMENU_SCALE;
	joinButton.rect.width = 475 * MAINMENU_SCALE;
	joinButton.action = Join;

	MenuItem quitButton;
	quitButton.rect.top = 720 * MAINMENU_SCALE;
	quitButton.rect.height = 750 * MAINMENU_SCALE;
	quitButton.rect.left = 376 * MAINMENU_SCALE;
	quitButton.rect.width = 476 * MAINMENU_SCALE;
	quitButton.action = Exit;

	_menuItems.push_back(debugButton);
	_menuItems.push_back(playButton);
	_menuItems.push_back(joinButton);
	_menuItems.push_back(quitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& menuItemRect.width > x)
		{
			return (*it).action;
		}
	}

	return Nothing;
}

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (window.pollEvent(menuEvent))
	{
		if (menuEvent.type == sf::Event::MouseButtonPressed)
		{
			return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
		}
		if (menuEvent.type == sf::Event::Closed)
		{
			return Exit;
		}
	}
}