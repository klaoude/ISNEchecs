#pragma once
#include <iostream>

#include "../Graphics/GameObject.h"

#include "../Main/PieceInfo.h"

class Piece : public GameObject
{
public:
	Piece();
	Piece(int ID, Type type, Couleur color, std::string textureID);
	~Piece();

	Type getType() { return m_type; }
	Couleur getColor() { return m_color; }
	int getID() { return m_ID; }
	std::string getTextureID() { return _textureID; }

	void setType(Type type) { m_type = type; }
	void setColor(Couleur couleur) { m_color = couleur; }	
	void setID(int ID) { m_ID = ID; }

	void draw(sf::RenderWindow& window);

private:
	Type m_type;
	Couleur m_color;

	int m_ID;

	std::string _textureID;
};
