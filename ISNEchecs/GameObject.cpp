#include "GameObject.h"

GameObject::GameObject()
{

}

GameObject::GameObject(sf::Texture texture)
{
	_texture = texture;
}

GameObject::GameObject(std::string texturePath)
{
	_texture.loadFromFile(texturePath);
}

GameObject::~GameObject()
{

}

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(_sprite);
}
