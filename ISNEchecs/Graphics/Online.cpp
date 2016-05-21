#include "Online.h"

Online::Online()
{}

void Online::init(sf::RenderWindow& window)
{
	sf::Image image;
	image.loadFromFile("Sprites/OnlineMenu.png");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.scale(MAINMENU_SCALE, MAINMENU_SCALE);

	window.draw(sprite);
	window.display();
}

MENUS Online::recevoirCoord(int x, int y)
{
	std::cout << "x = " << x << " y = " << y << std::endl;

	int lMenu = 0.365f*SCREEN_WIDTH;
	int rMenu = 0.6225f*SCREEN_WIDTH;
	int uMenu = 0.63f*SCREEN_HEIGHT;
	int dMenu = 0.75f*SCREEN_HEIGHT;

	int lMatchMaking = 0.3175f*SCREEN_WIDTH;
	int rMatchMaking = 0.69f*SCREEN_WIDTH;
	int uMatchMaking = 0.31f*SCREEN_HEIGHT;
	int dMatchMaking = 0.495f*SCREEN_HEIGHT;

	if (lMenu < x && rMenu > x && uMenu < y && dMenu > y)
	{
		return MENU;
	}
	
	if (lMatchMaking < x && rMatchMaking > x && uMatchMaking < y && dMatchMaking > y)
	{
		return FINDGAME;
	}
}