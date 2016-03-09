#pragma once

#include "Main\Piece.h"
#include "Main\Case.h"
#include "Main\Board.h"

class AI
{
public:
	AI(Board* board);
	~AI();

	void play();

private:
	int getSituationPoint(Piece piece, Case caze);
	bool canTake(Piece piece);
	Piece getMinVal(std::vector<Piece> vec);

	Board* _board;
	//Type _rangPiece[5] = { Type::REINE, Type::TOUR, Type::FOU, Type::CAVALIER, Type::ROI };
	Couleur _iaColor;
};

