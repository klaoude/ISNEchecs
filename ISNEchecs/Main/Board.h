#pragma once

#include <vector>

#include "../Graphics/GameObjectManager.h"

#include "../Main/Case.h"
#include "../Main/Piece.h"
#include "../Main/PieceInfo.h"
#include <SFML\Audio.hpp>
#include "../Son.h"

class Board
{
public:
	Board();
	Board(GameObjectManager* gom, Couleur mc);
	~Board();

	void setPiece(Piece* piece); 
	void delPiece(Piece piece);

	void movePieceTo(Piece* piece, Case caze, Couleur color);
	void mangePiece(Piece* piece, Case caze);
	void rock(Piece* piece, Case caze, std::string sens, Couleur color);

	bool movePiece(Piece* piece, Case caze);
	std::vector<Case> getBoard(){ return m_board; }
	Case getCase(int x, int y);
	Case getCase(int caseID);
	std::vector<Piece*> getAlivePiece() { return _alivePiece; }
	std::vector<Piece*> getAliveBlanc() { return _aliveBlanc; }
	std::vector<Piece*> getAliveNoir() { return _aliveNoir; }

	Couleur getMasterColor() { return _masterColor; }

	void simuleMove(Piece* piece, Case caze);
	void undoSimileMove();

private:
	std::vector<Case> m_board;
	GameObjectManager* _gom;
	Couleur _masterColor;
	Son* _hitmarker;

	std::vector<Piece*> _alivePiece;
	std::vector<Piece*> _aliveNoir;
	std::vector<Piece*> _aliveBlanc;

	//SimuleMove
	int s_oldCaseID;
	int s_newCaseID;
	Piece* s_pieceA;
	Piece* s_pieceB;
	//----------
};