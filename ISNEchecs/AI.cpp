#include "AI.h"

#include "Fonctions.h"
#include "canMove.h"

AI::AI(Board* board)
{
	_board = board;
}

AI::~AI()
{
}

/*
void AI::play()
{
	std::vector<Piece* > allPiece;
	if (_iaColor == BLANC)
		allPiece = _board->getAliveBlanc();
	else if (_iaColor == NOIR)
		allPiece = _board->getAliveNoir();

	auto canMovePiece = allPiece;

	for (int i = 0; i < allPiece.size(); i++)
	{
		if (getAllPath(_board, allPiece[i], _iaColor).size() == 0)
			canMovePiece.erase(canMovePiece.begin() + i);
	}

	for (int i = 0; i < canMovePiece.size(); i++)
	{

	}
}

int AI::getSituationPoint(Piece piece, Case caze)
{

}*/