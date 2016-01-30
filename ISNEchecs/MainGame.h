#pragma once
#include <SFML\Graphics.hpp>

class MainGame
{
public:
	MainGame();
	~MainGame();

	void start();

private:
	void init();
	void gameLoop();

	void handleInput();
	void draw();

	sf::RenderWindow* _window;
	int _screenWidth;
	int _screenHeight;

	std::string _windowTitle = "Chess";
};

