#pragma once

#include <vector>

#include "../Graphics/GameObjectManager.h"

#include "../Main/Case.h"
#include "../Main/Piece.h"
#include "../Main/PieceInfo.h"

class Board
{
public:
	Board();
	Board(GameObjectManager* gom);
	~Board();

	void setPiece(Piece* piece); 

	void movePiece(Piece* piece, Case caze);
	std::vector<Case> getBoard(){ return m_board; }
	Case getCase(int x, int y);
	Case getCase(int caseID);

private:
	std::vector<Case> m_board;
	GameObjectManager* _gom;
};