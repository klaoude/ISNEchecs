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
	Board(GameObjectManager* gom, Couleur mc);
	~Board();

	void setPiece(Piece* piece); 
	void delPiece(Piece piece);

	bool movePiece(Piece* piece, Case caze);
	std::vector<Case> getBoard(){ return m_board; }
	Case getCase(int x, int y);
	Case getCase(int caseID);

	std::vector<Piece*> getAlivePiece() { return _alivePiece; }
	std::vector<Piece*> getAliveBlanc() { return _aliveBlanc; }
	std::vector<Piece*> getAliveNoir() { return _aliveNoir; }

	Couleur getMasterColor() { return _masterColor; }

private:
	std::vector<Case> m_board;
	GameObjectManager* _gom;
	Couleur _masterColor;
	
	std::vector<Piece*> _alivePiece;
	std::vector<Piece*> _aliveNoir;
	std::vector<Piece*> _aliveBlanc;
};