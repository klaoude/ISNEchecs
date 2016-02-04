#pragma once
#include <iostream>

#include "PieceInfo.h"

class Piece
{
public:
	Piece();
	Piece(int ID, Type type, Couleur color);
	~Piece();

	Type getType() { return m_type; }
	Couleur getColor() { return m_color; }
	int getID() { return m_ID; }

	void setType(Type type) { m_type = type; }
	void setColor(Couleur couleur) { m_color = couleur; }	
	void setID(int ID) { ID = m_ID; }	

private:
	Type m_type;
	Couleur m_color;

	int m_ID;
};

