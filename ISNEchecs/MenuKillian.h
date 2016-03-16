#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

struct Point
{
public:
	Point() {}
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

	Button(){}
	Button(Point upleft, Point upright, Point downleft, Point downright);
	bool _Buttonclicked;
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
	MenuKillian();
	void init(sf::RenderWindow& window);
	void recevoir_coord(int x, int y);

private:	
	int _xclique;
	int _yclique;
};

Button::Button(Point upleft, Point upright, Point downleft, Point downright)
{
	_upleft=upleft;
	_upright=upright;
	_downleft=downleft;
	_downright=downright;
}
boolButton::_Buttonclicked
if (xclique)