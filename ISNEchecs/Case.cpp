#include "Case.h"

Case::Case(int px, int py, int ID)
{
	m_sx = 100;
	m_sy = 100;
	m_ID = ID;
}


Case::~Case()
{
}


void Case::setPieceCase(Piece piece)
{
	m_piece = piece;
}

void Case::delPiece()
{
	m_piece.setColor(NONEc);
	m_piece.setType(NONEt);
	m_piece.setID(NULL);
}