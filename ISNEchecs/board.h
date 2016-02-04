#pragma once

#include <vector>

#include "Case.h"
#include "Piece.h"
#include "PieceInfo.h"

class Board
{
public:
	Board();
	~Board();

	void setPiece(Piece piece); 

	void movePiece(Piece piece, int ID);

private:
	std::vector<Case> m_board;
};