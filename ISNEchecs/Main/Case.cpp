#include "../Main/Case.h"
#include "../Global.h"


Case::Case(int px, int py, int ID)
{
	m_sx = SCREEN_HEIGHT / 8;
	m_sy = SCREEN_WIDTH / 8;
	m_ID = ID;
	m_px = px;
	m_py = py;

	m_empty = true;

	m_piece = new Piece(NULL, NONEt, NONEc, "");
}


Case::~Case()
{
}


void Case::setPieceCase(Piece* piece)
{
	m_piece = piece;
}

void Case::delPiece()
{
	m_piece->setColor(NONEc);
	m_piece->setType(NONEt);
	m_piece->setID(NULL);
}