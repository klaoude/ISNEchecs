#include "MenuManager.h"

#include "MenuKillian.h"
#include "Options.h"
#include "Solo.h"
#include "Lan.h"
#include "Online.h"

MenuResult MenuManager::getState(sf::RenderWindow& window)
{
	sf::Event event, event2;
	
	while (window.pollEvent(event))
	{
		MenuKillian menu;
		menu.init(window);
		if (event.type == sf::Event::MouseButtonPressed)
		{
			MENUS coord = menu.recevoirCoord(event.mouseButton.x, event.mouseButton.y);
			if (coord == SOLO)
			{
				while (window.waitEvent(event2))
				{
					Solo menuSolo;
					menuSolo.init(window);
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuSolo.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);

						if (coord == CHOOSEBLACK)
						{
							return SOLONOIR;
						}

						if (coord == CHOOSEWHITE)
						{
							return SOLOBLANC;
						}

						if (coord == MENU)
						{
							break;
						}
					}
				}

			}

			if (coord == ONLINE)
			{
				while (window.waitEvent(event2))
				{
					Online menuOnline;
					menuOnline.init(window);
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuOnline.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);
						if (coord == FINDGAME)
						{
							return ONLINESEARCH;
						}

						if (coord == MENU)
						{
							break;
						}
					}
				}
			}
			std::cout << coord << std::endl;
			if (coord == LAN)
			{
				return DEBUG;
				while (window.waitEvent(event2))
				{
					Lan menuLan;
					menuLan.init(window);
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuLan.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);
						if (coord == PORTHOST)
						{
							//Ecrire dans la zone port de host
						}

						if (coord == HOST)
						{
							return LANHOST;
						}

						if (coord == PORTJOIN)
						{
							//Ecrire dans la zone port de join
						}

						if (coord == IP)
						{
							//Ecrire dans la zone IP
						}

						if (coord == JOIN)
						{
							return LANJOIN;
						}

						if (coord == MENU)
						{
							break;
						}
					}
				}
			}

			if (coord == OPTIONS)
			{
				while (window.waitEvent(event2))
				{
					Options menuOptions;
					menuOptions.init(window);
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuOptions.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);
						if (coord == SURBRI && SURBRILLANCE)
						{
							//Désactiver la surbrillance
						}

						if (coord == SURBRI && !SURBRILLANCE)
						{
							//Activer la surbrillance
						}

						if (coord == PSEUDO)
						{
							//Ecrire dans la zone pseudo
						}

						if (coord == RESOLUTION)
						{
							//Ecrire dans la zone Resolution
						}

						if (coord == MENU)
						{
							break;
						}
					}
				}
			}

			if (coord == EXIT)
			{
				return Exit;
			}
		}
	}
}