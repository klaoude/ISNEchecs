#include "MenuKillian.h"
#include "Global.h"

MenuKillian::MenuKillian()
{

}

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

void MenuKillian::recevoir_coord(int x, int y)
{
	_xclique = x;
	_yclique = y;
	std::cout << "coord x : " << x << " y : " << y << std::endl;
}


int main()
{
	Button(Point(126, 67), Point(302, 67), Point(126, 128), Point(302, 128));
	if (_Buttonclicked==true)
	{
		go_debug()
	}
}
