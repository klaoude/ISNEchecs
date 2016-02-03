#include "Piece.h"


Piece::Piece()
{
}

Piece::Piece(Type type, Couleur color, int ID)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
}

Piece::~Piece()
{
}