#pragma once

#include <SFML\Graphics.hpp>

struct Point
{
public:
	Point(int x, int y){ _x = x; _y = y; }
	
	void set(int x, int y){ _x = x; _y = y; }
	int getX();
	int getY();
private:
	int _x;
	int _y;
};

struct Button
{
private:
	Point _upleft;
	Point _upright;
	Point _downleft;
	Point _downright;
};

class MenuKillian
{
public:
	MenuKillian(int xclique, int yclique);
	void init();
	void recevoir_xclique();
	void recevoir_yclique();


private:
	
	int _xclique;
	int _yclique;

};
MenuKillian::MenuKillian(int xclique, int yclique)
_xclique=xclique
_yclique=yclique

void MenuKillian::init()
{

}

void MenuKillian::recevoir_xclique()
{

}

void MenuKillian::recevoir_xclique()
{

}