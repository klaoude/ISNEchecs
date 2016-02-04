#pragma once

#include <vector>

#include "Case.h"
#include "Piece.h"
#include "PieceInfo.h"
#include "GameObjectManager.h"

class Board
{
public:
	Board();
	Board(GameObjectManager gom);
	~Board();

	void setPiece(int ID, Type type, Couleur color); 

	void movePiece(Piece piece, int ID);

private:
	std::vector<Case> m_board;
	GameObjectManager _gom;
};