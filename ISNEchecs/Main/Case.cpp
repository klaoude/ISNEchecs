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

	m_piece = new Piece(0, NONEt, NONEc, "");
}


Case::~Case()
{
}


void Case::setPieceCase(Piece* piece)
{
	m_piece = piece;
	m_piece->setID(piece->getID());


}

void Case::delPiece()
{
	m_piece = new Piece(0, NONEt, NONEc, "");
	m_empty = true;
}

void Case::debugCase()
{
	std::cout << "[DEBUG CASE] : Piece = color : " << m_piece->getColor() << " ID : " << m_piece->getID() << std::endl;
	std::cout << "[DEBUG CASE] : Case ID : " << m_ID << std::endl;
}