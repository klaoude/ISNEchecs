#include "MainGame.h"
#include <iostream>

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}

void MainGame::start()
{
	init();
	gameLoop();
}

void MainGame::init()
{
	_window = new sf::RenderWindow(sf::VideoMode(200, 200), "Chess");
}

void MainGame::gameLoop()
{
	while (_window->isOpen())
	{
		handleInput();

		draw();
	}
}

void MainGame::handleInput()
{
	sf::Event event;


	while (_window->pollEvent(event)){
		if (event.type == sf::Event::EventType::Closed)
			_window->close();
		if (event.type == sf::Event::EventType::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				std::cout << "space bar press" << std::endl;
			}
		}
	}
}

void MainGame::draw()
{
	_window->clear();



	_window->display();
}