#include "Son.h"


Son::Son(std::string path)
{
	sf::SoundBuffer buffer;
	buffer.loadFromFile(path);
	_sound.setBuffer(buffer);
}

void Son::play()
{
	_sound.play();
}