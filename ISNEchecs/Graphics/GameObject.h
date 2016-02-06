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
	virtual sf::Vector2u getTextureSize() const { return _texture.getSize(); }

	virtual void setTexture(sf::Texture texture) { _sprite.setTexture(texture); _isLoaded = true; }
	virtual void setTexture(std::string texturePath);
	virtual void setPosition(float x, float y) { _sprite.setPosition(x, y); }
	virtual void scale(int scalex, int scaley);

	virtual bool IsLoaded() { return _isLoaded; }
	virtual void draw(sf::RenderWindow& window);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;

	bool _isLoaded;
};

