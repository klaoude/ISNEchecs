#include "MenuKillian.h"
#include "../Global.h"

MenuKillian::MenuKillian()
{}

void MenuKillian::init(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("Sprites/MainMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);

	window.draw(sprite);
	window.display();
}

MENUS MenuKillian::recevoirCoord(int x,int y)
{
	std::cout << "x = " << x << " y = " << y << std::endl;

	int lSolo = 0.3125f*SCREEN_WIDTH;
	int rSolo = 0.6875f*SCREEN_WIDTH;
	int uSolo = 0.2675f*SCREEN_HEIGHT;
	int dSolo = 0.3625f*SCREEN_HEIGHT;

	int lOnline = 0.3125f*SCREEN_WIDTH;
	int rOnline = 0.6875f*SCREEN_WIDTH;
	int uOnline = 0.3925f*SCREEN_HEIGHT;
	int dOnline = 0.4875f*SCREEN_HEIGHT;

	int lLan = 0.3125f*SCREEN_WIDTH;
	int rLan = 0.6875f*SCREEN_WIDTH;
	int uLan = 0.5175f*SCREEN_HEIGHT;
	int dLan = 0.6125f*SCREEN_HEIGHT;

	int lOptions = 0.3125f*SCREEN_WIDTH;
	int rOptions = 0.485f*SCREEN_WIDTH;
	int uOptions = 0.6425f*SCREEN_HEIGHT;
	int dOptions = 0.7375f*SCREEN_HEIGHT;

	int lExit = 0.5225f*SCREEN_WIDTH;
	int rExit = 0.6875f*SCREEN_WIDTH;
	int uExit = 0.6425f*SCREEN_HEIGHT;
	int dExit = 0.7375f*SCREEN_HEIGHT;

	if (lSolo < x && rSolo > x && uSolo < y && dSolo > y)
	{
		return SOLO;
	}

	if (lOnline < x && rOnline > x && uOnline < y && dOnline > y)
	{
		return ONLINE;
	}

	if (lLan < x && rLan > x && uLan < y && dLan > y)
	{
		return LAN;
	}

	if (lOptions < x && rOptions > x && uOptions < y && dOptions > y)
	{
		return OPTIONS;
	}

	if (lExit < x && rExit > x && uExit < y && dExit > y)
	{
		return EXIT;
	}
}