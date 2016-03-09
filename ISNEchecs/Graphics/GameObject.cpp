#include "../Graphics/GameObject.h"

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
	_texture.setSmooth(true);
	_sprite.setTexture(_texture);
	_isLoaded = true;
}

GameObject::~GameObject()
{

}

void GameObject::setTexture(std::string texturePath) 
{
	sf::Image image;
	image.loadFromFile(texturePath);
	image.createMaskFromColor(sf::Color::Red);
	_texture.loadFromImage(image);
	_sprite.setTexture(_texture);
	_isLoaded = true;
}

void GameObject::scale(float scalex, float scaley)
{
	_sprite.scale(scalex, scaley);
}

void GameObject::draw(sf::RenderWindow& window)
{
	if (IsLoaded()) 
	{
		window.draw(_sprite);
	}	
}
