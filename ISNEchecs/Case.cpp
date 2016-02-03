#include "Case.h"
#include "PieceInfo.h"



Case::Case(int px, int py, int ID)
{
	m_sx = 100;
	m_sy = 100;
	m_ID = ID;
}


Case::~Case()
{
}


void Case::setPieceCase(Type type, Couleur color, int ID)
{
	m_piece.setType(type);
	m_piece.setColor(color);
	m_ID = ID; 
}