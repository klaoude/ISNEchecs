#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void deleteFiles()
{
	system("rm -r Sound/ Sprites/ ISNEchecs.exe sfml-*.dll openal32 version.txt");
}

void deleteUpdaterFiles()
{
	system("rm update.zip newversion.txt");
}

int main(int argc, char** argv)
{
	system("wget --no-check-certificate -q -O - https://www.dropbox.com/s/paoxwz79j2p4uf6/version.txt?dl=0 > newversion.txt");
	float oldvers, newvers;

	std::ifstream infile("version.txt");
	if (infile.good())
	{
		std::string sLine;
		getline(infile, sLine);
		std::cout << "version actuelle : " << sLine << std::endl;
		oldvers = std::stof(sLine.c_str());
	}
	infile.close();

	infile = std::ifstream("newversion.txt");
	if (infile.good())
	{
		std::string sLine;
		getline(infile, sLine);
		std::cout << "derniere version : " << sLine << std::endl;
		newvers = std::stof(sLine.c_str());
	}
	infile.close();

	if (newvers > oldvers)
	{
		std::cout << "need update !" << std::endl;
		system("wget --no-check-certificate -q https://www.dropbox.com/s/ud4jgjhyfigqa4x/Release.zip?dl=0");
		system("mv file update.zip");
		deleteFiles();
		system("7za x -y update.zip");
		system("rm version.txt");
		system("mv newversion.txt version.txt");
		deleteUpdaterFiles();
	}
	else
		std::cout << "Your game is update !";
	system("Pause");
	return 0;
}