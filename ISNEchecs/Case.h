#pragma once
#include "Piece.h"

class Case
{
public:
	Case(int px, int py);
	~Case();
	bool isEmpty() { return m_empty; }
	void setPiece(Piece piece);
	void delPiece();
	Piece getPiece();

private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;
	bool m_empty;
	Piece m_piece;
};

