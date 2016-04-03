#include <iostream>
#include <fstream>

#include "MainGame.h"

int main(int argc, char** argv)
{
	system("wget --no-check-certificate -q -O - https://www.dropbox.com/s/paoxwz79j2p4uf6/version.txt?dl=0 > newversion.txt");
	float oldvers = 0.0f, newvers = 0.0f;

	std::ifstream infile("version.txt");
	if (infile.good())
	{
		std::string sLine;
		getline(infile, sLine);
		if (sLine != "")
		{
			std::cout << "version actuelle : " << sLine << std::endl;
			oldvers = std::stof(sLine.c_str());
		}
	}
	infile.close();

	infile = std::ifstream("newversion.txt");
	if (infile.good())
	{
		std::string sLine;
		getline(infile, sLine);
		if (sLine != "")
		{
			std::cout << "derniere version : " << sLine << std::endl;
			newvers = std::stof(sLine.c_str());
		}		
	}
	infile.close();

	system("rm newversion.txt");

	if (newvers > oldvers)
	{
		std::cout << "Your game is outdated please update (launch updater.exe)" << std::endl;
		system("Pause");
#ifdef _RELEASE
		return 0;
#endif
	}

	MainGame game;
	game.start();

	return 0;
}