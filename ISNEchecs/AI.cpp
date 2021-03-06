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
		if (i->second > max)
		{
			ret.clear();
			max = i->second;
			ret.push_back(i->first);
		}
		if (i->second == max)
			ret.push_back(i->first);
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
	/*
	*	Shema de reflexion :
	*		1: check si je peux me faire mang�
	*		2: check pour chaque move possible:
	*			si on bouge une piece qui est attack� (+/- 2*getVal(Piece))
	*			Si on bouge la bas est-ce qu'on est prot�g� ? (si oui +4)
	*			Si on bouge et que je peux me faire mang� (-4*getVal(Piece))
	*			Si je mange une piece enemie (+2*getVal(PieceEnemie))
	*			Si j'attaque une piece (+getVal(PieceAttack�))
	*		3: Check le move qui a le plus de points. En cas d'egalit� prend au hazard
	*		4: Move
	*/


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
			canMovePiece.erase(canMovePiece.begin() + (i - supr));
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
	if (oldid == _pieceNeddedToMove)
		point += _stepOne / 2;
	else
		point -= _stepOne;
	*_turnFile << point - oldpts << ":";
	std::cout << "[IA] Blue step : " << point - oldpts << std::endl;

	//Red
	oldpts = point;
	for each (Piece* ppiece in _myPiece)
	{
		if (isPossible(_board, *ppiece, caze, _board->getMasterColor(), true) && ppiece->getID() != oldid)
		{
			if (canMove(*_board, *ppiece, caze, _board->getMasterColor(), _echec, true))
			{
				std::cout << "[IA] Red Step -> " << ppiece->getID() << " protect " << caze.getID() << std::endl;
				if (piece.getType() == PION)
					point += 1;
				else
					point += 4;
				break;
			}
		}	
	}
	*_turnFile << point - oldpts << ":";
	std::cout << "[IA] Red step : " << point << std::endl;

	//Brown
	oldpts = point;
	for each(Piece* ppiece in _enemiPiece)
	{
		if (isPossible(&board, *ppiece, caze, _board->getMasterColor(), true))
		{
			std::cout << "is possible for " << ppiece->getID() << " to go " << caze.getID() << std::endl;
			if (canMove(board, *ppiece, caze, _board->getMasterColor(), _echec, true))
			{
				std::cout << "can move for " << ppiece->getID() << " to go " << caze.getID() << std::endl;
				point += -4 * getValPiece(&piece);
				break;
			}
		}
	}
	*_turnFile << point - oldpts << ":";

	//Green
	oldpts = point;
	if (caze.getPiece()->getColor() != _iaColor && caze.getPiece()->getColor() != Couleur::NONEc)
		point += 2 * getValPiece(caze.getPiece());
	*_turnFile << point - oldpts << ":";
	std::cout << "[IA] Green step : " << point << std::endl;
	
	//Cyan
	oldpts = point;
	for each(Piece* enemie in _enemiPiece)
	{
		if (isPossible(_board, piece, _board->getCase(enemie->getID()), _board->getMasterColor()))
			if (canMove(*_board, piece, _board->getCase(enemie->getID()), _board->getMasterColor(), _echec))
				point += getValPiece(enemie);
	}
	*_turnFile << point - oldpts << "/";
	std::cout << "[IA] Cyan step : " << point << std::endl;

	board.undoSimileMove();
	std::cout << "stopSimu" << std::endl;

	return point;
}

void AI::reloadMyPiece()
{
	std::vector<Piece* > allPiece;
	if (_iaColor == BLANC)
		allPiece = _board->getAliveBlanc();
	else if (_iaColor == NOIR)
		allPiece = _board->getAliveNoir();
	_myPiece = allPiece;
}

void AI::reloadEnemiPiece()
{
	std::vector<Piece*> enemyPiece;
	if (_iaColor == BLANC)
		enemyPiece = _board->getAliveNoir();
	else
		enemyPiece = _board->getAliveBlanc();
	_enemiPiece = enemyPiece;
}

int AI::enemyCanEatMe()
{
	int ret = 0;
	for each(Piece* enemi in _enemiPiece)
		for each(Piece* mi in _myPiece)
			if (isPossible(_board, *enemi, _board->getCase(mi->getID()), _board->getMasterColor()))
				if (canMove(*_board, *enemi, _board->getCase(mi->getID()), _board->getMasterColor(), _echec))
					if (getValPiece(mi) > ret)
					{
						ret = getValPiece(mi);
						_pieceNeddedToMove = mi->getID();
					}						
	return 2*ret;
}