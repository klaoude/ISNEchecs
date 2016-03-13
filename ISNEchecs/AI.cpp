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

std::vector<std::pair<Piece*, int>> returnMax(std::map<std::pair<Piece*, int>, int> map)
{
	int max = 0;
	auto maxId = map.begin()->first;
	std::vector<std::pair<Piece*, int>> ret;
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if (i->second > max)
		{
			max = i->second;
			ret.push_back(i->first);
		}
	}
	return ret;
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
		if (getAllPath(_board, allPiece[i], _board->getMasterColor()).size() == 0)
		{
			canMovePiece.erase(canMovePiece.begin() + (i-supr));
			supr++;
		}			
	}

	std::map<std::pair<Piece*, int>, int> map;
	for (int i = 0; i < canMovePiece.size(); i++)
	{
		auto allPath = getAllPath(_board, canMovePiece[i], _board->getMasterColor());
		for (int j = 0; j < allPath.size(); j++)
		{
			int situ = getSituationPoint(*canMovePiece[i], _board->getCase(allPath[j]));
			std::cout << situ << std::endl;
			std::pair<Piece*, int> tmpPair = std::make_pair(canMovePiece[i], allPath[j]);
			map.emplace(std::pair<std::pair<Piece*, int>, int>(tmpPair, situ));
		}
	}

	auto possibility = returnMax(map);
	int id = rand() % possibility.size();
	_board->movePiece(possibility[id].first, _board->getCase(possibility[id].second));
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
		if (canMove(board, *enemyPiece[i], caze, _board->getMasterColor(), Echec))
		{
			point -= getValPiece(&piece);
			std::cout << "je peux me faire manger ma piece si " << enemyPiece[i]->getID() << " viens sur la case " << caze.getID() << std::endl;
			break;
		}			
	}

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(board, piece, board.getCase(enemyPiece[i]->getID()), _board->getMasterColor(), Echec))
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