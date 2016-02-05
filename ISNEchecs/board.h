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
	Board(GameObjectManager* gom);
	~Board();

	void setPiece(Piece* piece); 

	void movePiece(Piece* piece, int ID);

	Case getCase(int x, int y);
private:
	std::vector<Case> m_board;
	GameObjectManager* _gom;
};