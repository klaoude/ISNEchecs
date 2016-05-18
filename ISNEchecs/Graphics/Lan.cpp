#include "Lan.h"
#include "../Global.h"

Lan::Lan()
{}

void Lan::init(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("Sprites/LanMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);

	window.draw(sprite);
	window.display();
}

MENUS Lan::recevoirCoord(int x, int y)
{
	std::cout << "x = " << x << " y = " << y << std::endl;

	//int lMenu;
	//int rMenu;
	//int uMenu;
	//int dMenu;

	//int lPlay = 0;
	//int rPlay = 0;
	//int uPlay = 0;
	//int dPlay = 0;

	//if (lMenu < x && rMenu > x && uMenu < y && dMenu > y)
	//{
	//	return MENU;
	//}

	//if (lPlay < x && rPlay > x && uPlay < y && dPlay > y)
	//{

	//}
	return MENU;
}