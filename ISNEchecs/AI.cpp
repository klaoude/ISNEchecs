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
	int max = -101;
	auto maxId = map.begin()->first;
	std::vector<std::pair<Piece*, int>> ret;
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if (i->second >= max)
		{
			max = i->second;
			ret.push_back(i->first);
		}
	}
	return ret;
}

Piece* returnMax(std::map<Piece*, int> map)
{
	int max = -101;
	auto maxId = map.begin()->first;
	Piece* ret;
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if (i->second >= max)
		{
			max = i->second;
			ret = i->first;
		}
	}
	return ret;
}

int returnMax(std::vector<int> vec)
{
	int max = -101;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] > max)
			max = vec[i];
	}
	return max;
}

void AI::play()
{
	std::vector<Piece* > allPiece;
	if (_iaColor == BLANC)
		allPiece = _board->getAliveBlanc();
	else if (_iaColor == NOIR)
		allPiece = _board->getAliveNoir();

	std::vector<Piece*> enemyPiece;
	if (_iaColor == BLANC)
		enemyPiece = _board->getAliveNoir();
	else
		enemyPiece = _board->getAliveBlanc();

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

	std::map<Piece*, int> pieceAttacked;

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		for (int j = 0; j < allPiece.size(); j++)
		{
			if (canMove(*_board, *enemyPiece[i], _board->getCase(allPiece[j]->getID()), _board->getMasterColor(), 0))
			{
				pieceAttacked.insert(std::pair<Piece*, int>(allPiece[j], getValPiece(allPiece[j])));
			}
		}
	}

	if (pieceAttacked.size() == 0)
	{
		std::map<std::pair<Piece*, int>, int> map;
		for (int i = 0; i < canMovePiece.size(); i++)
		{
			auto allPath = getAllPath(_board, canMovePiece[i], _board->getMasterColor());
			for (int j = 0; j < allPath.size(); j++)
			{
				int situ;
				if (canMovePiece[i]->getColor() != _board->getCase(allPath[j]).getPiece()->getColor() && _board->getCase(allPath[j]).getPiece()->getColor() != NONEc)
				{
					situ = getValPiece(_board->getCase(allPath[j]).getPiece()) * 2;
					_board->simuleMove(canMovePiece[i], _board->getCase(allPath[j]));

					std::vector<Piece*> enemyPiece;
					if (_iaColor == BLANC)
						enemyPiece = _board->getAliveNoir();
					else
						enemyPiece = _board->getAliveBlanc();

					int Echec = echec(_board);

					std::vector<int> vec;

					for each(Piece* piece in enemyPiece)
					{
						if (canMove(*_board, *piece, _board->getCase(canMovePiece[i]->getID()), _board->getMasterColor(), Echec))
							vec.push_back(getValPiece(piece));
					}

					_board->undoSimileMove();

					situ += (-2) * returnMax(vec);
				}
				else
				{
					situ = getSituationPoint(*canMovePiece[i], _board->getCase(allPath[j]), allPiece);
				}
				
				std::cout << situ << std::endl;
				std::pair<Piece*, int> tmpPair = std::make_pair(canMovePiece[i], allPath[j]);
				map.emplace(std::pair<std::pair<Piece*, int>, int>(tmpPair, situ));
			}
		}

		auto possibility = returnMax(map);
		int id;
		id = rand() % possibility.size();
		_board->movePiece(possibility[id].first, _board->getCase(possibility[id].second));
	}
	else
	{
		std::cout << "else statement" << std::endl;
		Piece* piece = returnMax(pieceAttacked);
		int val = getValPiece(piece);
		auto move = getAllPath(_board, piece, _board->getMasterColor());
		std::map<std::pair<Piece*, int>, int> map;

		for each(int var in move)
		{
			int situ = getSituationPoint(*piece, _board->getCase(var), allPiece);
			std::pair<Piece*, int> tmpPair = std::make_pair(piece, var);
			map.emplace(std::pair<std::pair<Piece*, int>, int>(tmpPair, situ));
		}

		auto possibility = returnMax(map);
		int id;
		id = rand() % possibility.size();
		_board->movePiece(possibility[id].first, _board->getCase(possibility[id].second));
	}	
}

int AI::getSituationPoint(Piece piece, Case caze, std::vector<Piece* > allPiece)
{
	std::cout << "start Simulation " << piece.getID() << " to " << caze.getID() << std::endl;
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
		if (canMove(board, piece, board.getCase(enemyPiece[i]->getID()), _board->getMasterColor(), Echec))
		{
			point += getValPiece(enemyPiece[i]);
			std::cout << "je peux manger sa piece si " << piece.getID() << " viens sur la case " << enemyPiece[i]->getID();
			
			board.getCase(caze.getID()).getPiece()->setColor(NOIR);
			bool canretake = false;
			for (int j = 0; j < allPiece.size(); j++)
			{
				if (canMove(board, *allPiece[j], caze, _board->getMasterColor(), Echec))
					canretake = true;
			}
			board.getCase(caze.getID()).getPiece()->setColor(BLANC);
			if (!canretake)
			{
				point -= 2*getValPiece(&piece) - 1;
				std::cout << " cependant je me fais niquer" << std::endl;
			}
			else
			{
				point -= getValPiece(&piece);
				std::cout << std::endl;
			}
				
		}
	}

	for (int i = 0; i < enemyPiece.size(); i++)
	{
		if (canMove(board, *enemyPiece[i], caze, _board->getMasterColor(), Echec))
		{
			point -= getValPiece(&piece);
			std::cout << "je peux me faire manger ma piece si " << enemyPiece[i]->getID() << " viens sur la case " << caze.getID() << std::endl;
		}
	}

	if (_iaColor == BLANC && Echec == 2)
		point += 4;
	if (_iaColor == NOIR && Echec == 1)
		point += 4;

	board.undoSimileMove();
	std::cout << "stopSimu" << std::endl;

	return point;
}