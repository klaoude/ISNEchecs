#include "AI.h"

#include <fstream>

#include "Fonctions.h"
#include "canMove.h"

AI::AI(Board* board)
{
	_board = board;
	_iaColor = BLANC;
	_turn = 0;
	_turnFile = new std::ofstream();
}

AI::~AI()
{

}

void AI::makeTurnFile()
{
	_turnFile->open("IAFiles/turn" + std::to_string(_turn) + ".txt");

	*_turnFile << "!" << std::endl;
	
	for each (Piece* piece in _board->getAlivePiece())	
		*_turnFile << piece->getType() << "/" << piece->getColor() << "/" << piece->getID() << "/";
	*_turnFile << std::endl;

	*_turnFile << "!" << std::endl;

	*_turnFile << _iaColor << "/";
}

std::vector<std::pair<Piece*, int>> AI::returnMax(std::map<std::pair<Piece*, int>, int> map)
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


	std::map<std::pair<Piece*, int>, int> mapPoint;

	//init vars
	_turn++;
	makeTurnFile();

	reloadMyPiece();

	reloadEnemiPiece();

	_echec = echec(_board);
	//---------

	//AI vars
	_stepOne = enemyCanEatMe();
	//-------

	//set canMovePiece for opti
	auto canMovePiece = _myPiece;
	int supr = 0;
	for (int i = 0; i < _myPiece.size(); i++)
	{
		if (getAllPath(_board, _myPiece[i], _board->getMasterColor()).size() == 0)
		{
			canMovePiece.erase(canMovePiece.begin() + (i-supr));
			supr++;
		}			
	}
	//-------------------------

	for (int i = 0; i < canMovePiece.size(); i++)
	{
		auto allPath = getAllPath(_board, canMovePiece[i], _board->getMasterColor());
		for (int j = 0; j < allPath.size(); j++)
		{
			mapPoint.insert(std::pair<std::pair<Piece*, int>, int>(std::pair<Piece*, int>(canMovePiece[i], allPath[j]), getSituationPoint(*canMovePiece[i], _board->getCase(allPath[j]))));
			}
		}
	*_turnFile << std::endl << "!" << std::endl;

	//best Move
	auto possibility = returnMax(mapPoint);
	int id;
	id = rand() % possibility.size();
	std::cout << "[AI] i move " << possibility[id].first->getID() << " to " << _board->getCase(possibility[id].second).getID() << std::endl;
	*_turnFile << possibility[id].first->getID() << "-" << _board->getCase(possibility[id].second).getID() << std::endl;
	_board->movePiece(possibility[id].first, _board->getCase(possibility[id].second));	
	_turnFile->close();
	//---------

	/*
	if (pieceAttacked.size() == 0) //si une de nos piece est attaqué
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
	else //si aucune de nos piece est attaqué
	{
		std::cout << "else statement" << std::endl;
		Piece* piece = returnMax(pieceAttacked);
		int val = getValPiece(piece);
		auto move = getAllPath(_board, piece, _board->getMasterColor());
		std::map<std::pair<Piece*, int>, int> map;
		int situ;

		for each(int var in move)
		{
			situ = getSituationPoint(*piece, _board->getCase(var), allPiece);
			std::pair<Piece*, int> tmpPair = std::make_pair(piece, var);
			map.emplace(std::pair<std::pair<Piece*, int>, int>(tmpPair, situ));
		}

		auto possibility = returnMax(map);
		int id;
		id = rand() % possibility.size();
		_board->movePiece(possibility[id].first, _board->getCase(possibility[id].second));
		std::cout << situ << std::endl;
	}	*/
	}	

int AI::getSituationPoint(Piece piece, Case caze)
{
	*_turnFile << piece.getID() << "-" << caze.getID() << "/";

	std::cout << "start Simulation " << piece.getID() << " to " << caze.getID() << std::endl;
	int point = 0;
	Board board = *_board;
	int oldid = piece.getID();
	board.simuleMove(&piece, caze);

	//Blue
	int oldpts = point;	
	if (&piece == _pieceNeddedToMove)
		point += _stepOne / 2;
	else
		point -= _stepOne;
	*_turnFile << point - oldpts << ":";
	std::cout << "[IA] Blue step : " << point - oldpts << std::endl;

	//Red
	oldpts = point;
	for each (Piece* ppiece in _myPiece)
	{
		if (isPossible(_board, *ppiece, caze, _iaColor) && ppiece->getID() != oldid)
		{
			if (canMove(*_board, *ppiece, caze, _iaColor, _echec))
			{
				std::cout << "[IA] Red Step -> " << ppiece->getID() << " protect " << caze.getID() << std::endl;
				point += 4;
				break;
			}
			}
			}
	*_turnFile << point - oldpts << ":";
	std::cout << "[IA] Red step : " << point << std::endl;
				
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