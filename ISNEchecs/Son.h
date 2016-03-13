#pragma once

#include <iostream>
#include <SFML\Audio.hpp>

class Son
{
public:
	Son(std::string path);
	
	void play();

private:
	sf::Sound _sound;
};