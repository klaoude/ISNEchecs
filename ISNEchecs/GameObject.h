#pragma once
#include <SFML\Graphics.hpp>

class GameObject
{
public:
	GameObject();
	GameObject(sf::Texture texture);
	GameObject(std::string texturePath);
	~GameObject();

	sf::Sprite getSprite() { return _sprite; }
	sf::Vector2f GetPosition() { return _sprite.getPosition(); }

	void setTexture(sf::Texture texture) { _texture = texture; }
	void setTexture(std::string texturePath) { _texture.loadFromFile(texturePath); }
	void setPosition(float x, float y) { _sprite.setPosition(x, y); }

	void draw(sf::RenderWindow& window);

private:
	sf::Sprite _sprite;
	sf::Texture _texture;
};

