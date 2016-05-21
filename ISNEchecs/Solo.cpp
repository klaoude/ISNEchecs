#include "Solo.h"
#include "Global.h"

Solo::Solo()
{}

void Solo::init(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("Sprites/SoloMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);

	window.draw(sprite);
	window.display();
}

MENUS Solo::recevoirCoord(int x, int y)
{
	std::cout << "x = " << x << " y = " << y << std::endl;

	int lMenu = 0.3775f*SCREEN_WIDTH;
	int rMenu = 0.63f*SCREEN_WIDTH;
	int uMenu = 0.6875f*SCREEN_HEIGHT;
	int dMenu = 0.82f*SCREEN_HEIGHT;

	int lPlayBlack = 0.1325f*SCREEN_WIDTH;
	int rPlayBlack = 0.47f*SCREEN_WIDTH;
	int uPlayBlack = 0.32f*SCREEN_HEIGHT;
	int dPlayBlack = 0.47f*SCREEN_HEIGHT;

	int lPlayWhite = 0.5275f*SCREEN_WIDTH;
	int rPlayWhite = 0.875f*SCREEN_WIDTH;
	int uPlayWhite = 0.32f*SCREEN_HEIGHT;
	int dPlayWhite = 0.47f*SCREEN_HEIGHT;

	if (lMenu < x && rMenu > x && uMenu < y && dMenu > y)
	{
		return MENU;
	}

	if (lPlayBlack < x && rPlayBlack > x && uPlayBlack < y && dPlayBlack > y)
	{
		return CHOOSEBLACK;
	}
	
	if (lPlayWhite < x && rPlayWhite > x && uPlayWhite < y && dPlayWhite > y)
	{
		return CHOOSEWHITE;
	}
}