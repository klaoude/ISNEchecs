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
	bool getHasMoved() { return m_hasMoved; }

	void setType(Type type) { m_type = type; }
	void setColor(Couleur couleur) { m_color = couleur; }	
	void setID(int ID) { m_ID = ID; }
	void setHasMoved(bool hasMoved) { m_hasMoved = hasMoved; }

	void draw(sf::RenderWindow& window);

	void del();

private:
	Type m_type;
	Couleur m_color;
	bool m_hasMoved;
	int m_ID;

	std::string _textureID;
};

