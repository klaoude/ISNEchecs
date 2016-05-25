#include <sstream>

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
	
	sf::Font font;
	font.loadFromFile("Font/CSMS.ttf");
	
	textPorthost.setFont(font);
	textPorthost.setCharacterSize(SCREEN_HEIGHT / 25.f);
	textPorthost.setColor(sf::Color::White);
	textPorthost.setPosition(SCREEN_HEIGHT / (500 / 172.f), SCREEN_WIDTH / (500 / 106.f));

	textPortjoin.setFont(font);
	textPortjoin.setCharacterSize(SCREEN_HEIGHT / 25.f);
	textPortjoin.setColor(sf::Color::White);
	textPortjoin.setPosition(SCREEN_HEIGHT / (500 / 172.f), SCREEN_WIDTH / (500 / 230.f));

	textIp.setFont(font);
	textIp.setCharacterSize(SCREEN_HEIGHT / 25.f);
	textIp.setColor(sf::Color::White);
	textIp.setPosition(SCREEN_HEIGHT / (500 / 144.f), SCREEN_WIDTH / (500 / 310.f));

	bool porthost = false;
	bool portjoin = false;
	bool ip = false;	

	while (window.waitEvent(event))
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
				Lan menuLan;
				menuLan.init(window);
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
						else if (event2.text.unicode == 8)
						{
							if (porthost)
							{
								std::string str = textPorthost.getString();
								if (str.size() > 0)
									str.pop_back();
								textPorthost.setString(str);
							}
							else if (portjoin)
							{
								std::string str = textPortjoin.getString();
								if (str.size() > 0)
									str.pop_back();
								textPortjoin.setString(str);
							}
							else if (ip)
							{
								std::string str = textIp.getString();
								if (str.size() > 0)
									str.pop_back();
								textIp.setString(str);
							}

							window.clear();
							menuLan.init(window);
							window.display();
						}
						else
						{
							if (porthost && textPorthost.getString().getSize() < 5)
								textPorthost.setString(textPorthost.getString() + static_cast<char>(event2.text.unicode));
							if(portjoin && textPortjoin.getString().getSize() < 5)
								textPortjoin.setString(textPortjoin.getString() + static_cast<char>(event2.text.unicode));
							if(ip && textIp.getString().getSize() < 15)
								textIp.setString(textIp.getString() + static_cast<char>(event2.text.unicode));
							
							window.display(); // 2 times display for prevent some bugs
						}

						window.draw(textPorthost);
						window.draw(textPortjoin);
						window.draw(textIp);

						window.display();
					}
					
					if (event2.type == sf::Event::MouseButtonPressed)
					{
						coord = menuLan.recevoirCoord(event2.mouseButton.x, event2.mouseButton.y);
						if (coord == PORTHOST)
						{
							porthost = true;
							portjoin = false;
							ip = false;
						}

						if (coord == HOST)
						{
							return LANHOST;
						}

						if (coord == PORTJOIN)
						{
							portjoin = true;
							porthost = false;
							ip = false;
						}

						if (coord == IP)
						{
							ip = true;
							portjoin = false;
							porthost = false;
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