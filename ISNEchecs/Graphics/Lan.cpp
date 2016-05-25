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

	int lPortHost = 0.186f*SCREEN_WIDTH;
	int rPortHost = 0.504f*SCREEN_WIDTH;
	int uPortHost = 0.186f*SCREEN_HEIGHT;
	int dPortHost = 0.314f*SCREEN_HEIGHT;

	int lPortJoin = 0.186f*SCREEN_WIDTH;
	int rPortJoin = 0.504f*SCREEN_WIDTH;
	int uPortJoin = 0.442f*SCREEN_HEIGHT;
	int dPortJoin = 0.558f*SCREEN_HEIGHT;

	int lIp = 0.186f*SCREEN_WIDTH;
	int rIp = 0.504f*SCREEN_WIDTH;
	int uIp = 0.592f*SCREEN_HEIGHT;
	int dIp = 0.686f*SCREEN_HEIGHT;

	int lhost = 0.564f*SCREEN_WIDTH;
	int rhost = 0.812f*SCREEN_WIDTH;
	int uhost = 0.19f*SCREEN_HEIGHT;
	int dhost = 0.314f*SCREEN_HEIGHT;

	int ljoin = 0.564f*SCREEN_WIDTH;
	int rjoin = 0.812f*SCREEN_WIDTH;
	int ujoin = 0.504f*SCREEN_HEIGHT;
	int djoin = 0.622f*SCREEN_HEIGHT;

	int lExit = 0.374f*SCREEN_WIDTH;
	int rExit = 0.622f*SCREEN_WIDTH;
	int uExit = 0.758f*SCREEN_HEIGHT;
	int dExit = 0.88f*SCREEN_HEIGHT;

	if (lPortHost < x && rPortHost > x && uPortHost < y && dPortHost > y)
	{
		return PORTHOST;
	}

	if (lPortJoin < x && rPortJoin > x && uPortJoin < y && dPortJoin > y)
	{
		return PORTJOIN;
	}

	if (ljoin < x && rjoin > x && ujoin < y && djoin > y)
	{
		return JOIN;
	}

	if (lhost < x && rhost > x && uhost < y && dhost > y)
	{
		return HOST;
	}

	if (lIp < x && rIp > x && uIp < y && dIp > y)
	{
		return IP;
	}

	if (lExit < x && rExit > x && uExit < y && dExit > y)
	{
		return MENU;
	}
}