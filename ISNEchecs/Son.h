#pragma once

#include <iostream>
#include <SFML\Audio.hpp>

class Son
{
public:
	Son() {}

	explicit Son(std::string path);
	
	void setBuffer();
	void play();

private:
	sf::SoundBuffer _buffer;
	sf::Sound _sound;
};