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
		auto allPath = getAllPath(_board, canMovePiece[i], _iaColor);
		for (int j = 0; j < allPath.size(); i++)
		{
			std::cout << getSituationPoint(*canMovePiece[i], _board->getCase(allPath[j])) << std::endl;
		}
	}
}

int AI::getSituationPoint(Piece piece, Case caze)
{
	int point = 0;
	_board->simuleMove(&piece, caze);

	std::vector<Piece*> enemyPiece;
	if (_iaColor == BLANC)
		enemyPiece = _board->getAliveNoir();
	else
		enemyPiece = _board->getAliveBlanc();

	int Echec = echec(_board);

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(_board, *enemyPiece[i], caze, _iaColor, Echec))
		{
			point -= getValPiece(&piece);
			break;
		}			
	}

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(_board, piece, _board->getCase(enemyPiece[i]->getID()), _iaColor, Echec))
		{
			point += getValPiece(enemyPiece[i]);
			break;
		}
	}

	if (_iaColor == BLANC && Echec == 2)
		point += 4;
	if (_iaColor == NOIR && Echec == 1)
		point += 4;

	if (Echec)

	return point;
}