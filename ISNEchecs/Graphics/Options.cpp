#include "Options.h"

Options::Options()
{}

void Options::init(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("Sprites/OptionsMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);

	window.draw(sprite);
	window.display();
}

MENUS Options::recevoirCoord(int x, int y)
{
	std::cout << "x = " << x << " y = " << y << std::endl;

	int lSurbrillance = 0.3125f*SCREEN_WIDTH;
	int rSurbrillance = 0.6875f*SCREEN_WIDTH;
	int uSurbrillance = 0.2575f*SCREEN_HEIGHT;
	int dSurbrillance = 0.3625f*SCREEN_HEIGHT;

	int lPseudo = 0.3125f*SCREEN_WIDTH;
	int rPseudo = 0.6875f*SCREEN_WIDTH;
	int uPseudo = 0.385f*SCREEN_HEIGHT;
	int dPseudo = 0.4875f*SCREEN_HEIGHT;

	int lResolution = 0.3125f*SCREEN_WIDTH;
	int rResolution = 0.6875f*SCREEN_WIDTH;
	int uResolution = 0.5175f*SCREEN_HEIGHT;
	int dResolution = 0.6125f*SCREEN_HEIGHT;

	int lExit = 0.3125f*SCREEN_WIDTH;
	int rExit = 0.6875f*SCREEN_WIDTH;
	int uExit = 0.6425f*SCREEN_HEIGHT;
	int dExit = 0.735f*SCREEN_HEIGHT;

	if (lSurbrillance < x && rSurbrillance > x && uSurbrillance < y && dSurbrillance > y)
	{
		return SURBRI;
	}

	if (lPseudo < x && rPseudo > x && uPseudo < y && dPseudo > y)
	{
		return PSEUDO;
	}

	if (lResolution < x && rResolution < x && uResolution < y && dResolution > y)
	{
		return RESOLUTION;
	}

	if (lExit < x && rExit > x && uExit < y && dExit > y)
	{
		return MENU;
	}
}