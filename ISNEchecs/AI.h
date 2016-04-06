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
	void makeTurnFile();

	int getSituationPoint(Piece piece, Case caze);
	bool canTake(Piece piece);
	Piece getMinVal(std::vector<Piece> vec);
	std::vector<int> canEat(std::vector<Piece*> allPiece);
	int enemyCanEatMe();

	void reloadMyPiece();
	void reloadEnemiPiece();

	std::vector<std::pair<Piece*, int>> returnMax(std::map<std::pair<Piece*, int>, int> map);

	int _stepOne;

	Board* _board;
	Couleur _iaColor;
	std::vector<Piece*> _myPiece;
	std::vector<Piece*> _enemiPiece;
	int _pieceNeddedToMove;
	int _echec;
	int _turn;
	std::ofstream* _turnFile;
};

