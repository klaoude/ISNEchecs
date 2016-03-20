#include "Son.h"


Son::Son(std::string path)
{
	_buffer.loadFromFile(path);
}

void Son::setBuffer()
{
	_sound.setBuffer(_buffer);
}

void Son::play()
{
	std::cout << "caca" << std::endl;
	_sound.play();
}