#pragma once
#include "Piece.h"

class Case
{
public:
	Case(int px, int py, int ID);
	~Case();
	bool isEmpty() { return m_empty; }
	bool setEmpty(bool choice) { m_empty = choice; }
	int getID() { return m_ID; }
	void setPieceCase(Type type, Couleur color, int ID);
	Piece getPiece() { return m_piece; }


private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;
	bool m_empty;
	int m_ID;
	Piece m_piece;
};

