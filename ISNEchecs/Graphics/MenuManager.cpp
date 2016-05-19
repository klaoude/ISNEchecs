#include "MenuManager.h"

#include "MenuKillian.h"
#include "Options.h"
#include "Solo.h"
#include "Lan.h"
#include "Online.h"

MenuResult MenuManager::getState(sf::RenderWindow& window)
{
	sf::Event event, event2;
	sf::Text textPorthost, textPortjoin, textIp;
	bool porthost = false;
	bool portjoin = false;
	bool ip = false;
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
			if (coord == LAN)
			{
				return DEBUG;
				while (window.waitEvent(event2))
				{
					if(event2.type == sf::Event::TextEntered)
					{
						if(event2.text.unicode == 13)
						{
							porthost = false;
							portjoin = false;
							ip = false;
						}
						else
						{
							if(porthost)
								textPorthost.setString(textPorthost.getString() + static_cast<char>(event.text.unicode));
							if(portjoin)
								textPortjoin.setString(textPortjoin.getString() + static_cast<char>(event.text.unicode));
							if(ip)
								textIp.setString(textIp.getString() + static_cast<char>(event.text.unicode));
						}											
					}
					Lan menuLan;
					menuLan.init(window);
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuLan.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);
						if (coord == PORTHOST)
						{
							porthost = true;
						}

						if (coord == HOST)
						{
							return LANHOST;
						}

						if (coord == PORTJOIN)
						{
							portjoin = true;
						}

						if (coord == IP)
						{
							ip = true;
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