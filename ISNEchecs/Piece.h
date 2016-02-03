#pragma once
#include <iostream>
#include "PieceInfo.h"



class Piece
{
public:
	Piece();
	Piece(Type type, Couleur color, int ID);
	~Piece();
	Type getType() { return m_type; }
	Couleur getColor() { return m_color; }
	void setType(Type type) { m_type = type; }
	void setColor(Couleur couleur) { m_color = couleur; }
	int getID() { return m_ID; }
	int setID(int ID) { ID = m_ID; }
	

private:
	Type m_type;
	Couleur m_color;
	int m_ID;
};

