#pragma once

#include <SFML\Graphics.hpp>

#include "../Global.h"

class MenuKillian;
class Lan;
class Options;
class Online;
class Solo;

enum MenuResult
{
	DEBUG,

	SOLONOIR,
	SOLOBLANC,

	LANHOST,
	LANJOIN,

	ONLINESEARCH,

	Exit
};

enum MENUS
{
	SOLO,
	CHOOSEBLACK,
	CHOOSEWHITE,

	ONLINE,
	FINDGAME,

	LAN,
	PORTHOST,
	PORTJOIN,
	IP,
	HOST,
	JOIN,

	OPTIONS,
	SURBRI,
	PSEUDO,
	RESOLUTION,

	MENU,
	EXIT,

	NOTHING
};

class MenuManager
{
public:
	MenuResult getState(sf::RenderWindow& window);
private:
};