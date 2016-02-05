#pragma once
#include "Piece.h"

class Case
{
public:
	Case(int px, int py, int ID);
	~Case();

	void setEmpty(bool choice) { m_empty = choice; }

	int getID() { return m_ID; }
	Piece* getPiece() { return m_piece; }

	bool isEmpty() { return m_empty; }	
	
	void setPieceCase(Piece* piece);
	void delPiece();

	int get_px(){ return m_px; }
	int get_py(){ return m_py; }

private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;

	int m_ID;

	bool m_empty;

	Piece* m_piece;
};

