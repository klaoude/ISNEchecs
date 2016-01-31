#include "Case.h"
#include "Piece.h"

Case::Case(int px, int py) : m_piece(Type::NONE,Couleur::NONEc)
{
	m_sx = 100;
	m_sy = 100;

}


Case::~Case()
{
}


void Case::setPiece(Piece piece)
{
	m_empty = 0;
	m_piece = piece;
}

void Case::delPiece()
{
	m_empty = 1;
	m_piece = Piece(Type::NONE, Couleur::NONEc);
}

Piece Case::getPiece()
{
	return m_piece;
}