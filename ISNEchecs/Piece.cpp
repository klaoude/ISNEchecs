#include "Piece.h"


Piece::Piece(Type type, Couleur color)
{
	m_type = type;
	m_color = color;
}


Piece::~Piece()
{
}

void Piece::setType(Type type)
{
	m_type = type;
}


void Piece::setColor(Couleur couleur)
{
	m_color = couleur;
}
