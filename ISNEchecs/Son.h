#pragma once

#include <iostream>
#include <SFML\Audio.hpp>

class Son
{
public:
	Son() {}
	Son(std::string path);
	
	void play();

private:
	sf::Sound _sound;
};