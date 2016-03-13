#include "AI.h"

#include "Fonctions.h"
#include "canMove.h"

AI::AI(Board* board)
{
	_board = board;
	_iaColor = BLANC;
}

AI::~AI()
{
}

std::pair<Piece*, int> returnMax(std::map<std::pair<Piece*, int>, int> map)
{
	int max = 0;
	auto maxId = map.begin()->first;
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if (i->second > max)
		{
			max = i->second;
			maxId = i->first;
		}
	}
	return maxId;
}

void AI::play()
{
	std::vector<Piece* > allPiece;
	if (_iaColor == BLANC)
		allPiece = _board->getAliveBlanc();
	else if (_iaColor == NOIR)
		allPiece = _board->getAliveNoir();

	auto canMovePiece = allPiece;
	int supr = 0;

	for (int i = 0; i < allPiece.size(); i++)
	{
		if (getAllPath(_board, allPiece[i], _iaColor).size() == 0)
		{
			canMovePiece.erase(canMovePiece.begin() + (i-supr));
			supr++;
		}			
	}

	std::map<std::pair<Piece*, int>, int> map;
	for (int i = 0; i < canMovePiece.size(); i++)
	{
		auto allPath = getAllPath(_board, canMovePiece[i], _iaColor);
		for (int j = 0; j < allPath.size(); j++)
		{
			int situ = getSituationPoint(*canMovePiece[i], _board->getCase(allPath[j]));
			std::cout << situ << std::endl;
			std::pair<Piece*, int> tmpPair = std::make_pair(canMovePiece[i], allPath[j]);
			map.emplace(std::pair<std::pair<Piece*, int>, int>(tmpPair, situ));
		}
	}

	std::cout << "IA move piece : " << returnMax(map).first->getID() << " to case : " << returnMax(map).second << std::endl;
	_board->movePiece(returnMax(map).first, _board->getCase(returnMax(map).second));
}

int AI::getSituationPoint(Piece piece, Case caze)
{
	int point = 0;
	Board board = *_board;
	board.simuleMove(&piece, caze);

	std::vector<Piece*> enemyPiece;
	if (_iaColor == BLANC)
		enemyPiece = board.getAliveNoir();
	else
		enemyPiece = board.getAliveBlanc();

	int Echec = echec(&board);

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(board, *enemyPiece[i], caze, _iaColor, Echec))
		{
			point -= getValPiece(&piece);
			break;
		}			
	}

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(board, piece, board.getCase(enemyPiece[i]->getID()), _iaColor, Echec))
		{
			point += getValPiece(enemyPiece[i]);
			break;
		}
	}

	if (_iaColor == BLANC && Echec == 2)
		point += 4;
	if (_iaColor == NOIR && Echec == 1)
		point += 4;

	board.undoSimileMove();

	return point;
}