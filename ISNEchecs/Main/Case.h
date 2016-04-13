#pragma once

#include "../Main/Piece.h"

class Case
{
public:
	Case(int px, int py, int ID);
	~Case();

	void setEmpty(bool choice) { m_empty = choice; }

	int getID() const	{ return m_ID; }
	Piece* getPiece() const	{ return m_piece; }

	bool isEmpty() const	{ return m_empty; }	
	void setPieceCase(Piece* piece);
	void delPiece();
	Case* pcase() { return this; }

	int get_px() const	{ return m_px; }
	int get_py() const	{ return m_py; }

	sf::Vector2u getPos() const	{ return sf::Vector2u(m_px, m_py); }

	void debugCase() const;

private:
	int m_sx;
	int m_sy;
	int m_px;
	int m_py;

	int m_ID;

	bool m_empty;

	Piece* m_piece;
};

