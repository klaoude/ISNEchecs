#pragma once

#include "Main\Piece.h"
#include "Main\Case.h"
#include "Main\Board.h"

class AI
{
public:
	AI() {}
	AI(Board* board);
	~AI();

	void play();

private:
	int getSituationPoint(Piece piece, Case caze, std::vector<Piece* > allPiece);
	bool canTake(Piece piece);
	Piece getMinVal(std::vector<Piece> vec);
	std::vector<int> canEat(std::vector<Piece*> allPiece);
	int enemyCanEatMe();

	void reloadMyPiece();
	void reloadEnemiPiece();

	Board* _board;
	Couleur _iaColor;
	std::vector<Piece*> _myPiece;
	std::vector<Piece*> _enemiPiece;
	Piece* _pieceNeddedToMove;
	int _echec;
};

