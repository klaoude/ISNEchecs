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
public:
	Button(Point upleft, Point upright, Point downleft, Point downright);
	
	void go_debug();
		
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
	void recevoir_coord();


private:
	
	int _xclique;
	int _yclique;

};
MenuKillian::MenuKillian(int xclique, int yclique)
{
	_xclique = xclique;
	_yclique = yclique;
}

Button::Button(Point upleft, Point upright, Point downleft, Point downright)
{
	_upleft=upleft;
	_upright=upright;
	_downleft=downleft;
	_downright=downright;
}
void MenuKillian::init()
{

}

void MenuKillian::recevoir_coord()
{

}

int main()
{

}