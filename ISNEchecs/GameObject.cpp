#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(sf::Texture texture)
{
	_texture = texture;
	_isLoaded = true;
}

GameObject::GameObject(std::string texturePath)
{
	_texture.loadFromFile(texturePath);
	_isLoaded = true;
}

GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow& window)
{
	if (IsLoaded()) 
	{
		window.draw(_sprite);
	}	
}
