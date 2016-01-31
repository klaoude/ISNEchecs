#pragma once
#include "Piece.h"

class Case
{
public:
	Case(int px, int py, int ID);
	~Case();
	bool isEmpty() { return m_empty; }
	bool setEmpty(bool choice) { m_empty = choice; }
	void setPiece(Piece piece);
	void delPiece();
	Piece getPiece();
	int getID() { return m_ID; }

private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;
	bool m_empty;
	Piece m_piece;
	int m_ID;
};

