#include "Piece.h"

Piece::Piece()
{
}

Piece::Piece(int ID, Type type, Couleur color)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
}

Piece::~Piece()
{
}