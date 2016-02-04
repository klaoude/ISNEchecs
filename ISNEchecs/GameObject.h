#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class GameObject
{
public:
	GameObject();
	GameObject(sf::Texture texture);
	GameObject(std::string texturePath);
	~GameObject();

	virtual sf::Sprite getSprite() const { return _sprite; }
	virtual sf::Vector2f GetPosition() const { return _sprite.getPosition(); }

	virtual void setTexture(sf::Texture texture) { _texture = texture; std::cout << "texture loaded" << std::endl; }
	virtual void setTexture(std::string texturePath) { _texture.loadFromFile(texturePath); }
	virtual void setPosition(float x, float y) { _sprite.setPosition(x, y); }

	virtual void draw(sf::RenderWindow& window);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
};

