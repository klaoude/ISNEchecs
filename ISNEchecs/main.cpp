#include <iostream>

#include "MainGame.h"

void thread(int* i, bool* stop)
{
	std::cout << "stop adress :" << stop << std::endl;
	int j;
	for (j = 0; j < 150; j++)
	{
		std::cout << "j++, new val :" << j << std::endl;
		*i = j;
		if (*stop == false)
			break;
	}
	std::cout << "i adress :" << i << std::endl;
	std::cout << "i final val :" << *i << std::endl;
}

int main(int argc, char** argv)
{
	int i = 0;
	bool stop = true;
	//std::thread test(thread, &i, &stop);

	//while (stop)
		//if (i == 50)
			//stop = false;

	MainGame game;
	game.start();

	return 0;
}