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
	bool AI::enemyCanEatMe(std::vector<Piece*> enemiPiece, int caseid);

	Board* _board;
	Couleur _iaColor;
};

