#pragma once

#include <vector>

#include "../Graphics/GameObjectManager.h"
#include "../Graphics/Promote.h"

#include "../Main/Case.h"
#include "../Main/Piece.h"
#include "../Main/PieceInfo.h"

#include "../Son.h"

class Trashbin;

class Board
{
public:
	Board();
	Board(GameObjectManager* gom, Couleur mc, Trashbin& trash, sf::RenderWindow& window);
	~Board();

	void setPiece(Piece* piece); 

	void movePieceTo(Piece* piece, Case caze, Couleur color);
	void mangePiece(Piece* piece, Case caze);
	void rock(Piece* piece, Case caze, std::string sens, Couleur color);

	bool movePiece(Piece* piece, Case caze);
	std::vector<Case> getBoard() const { return m_board; }
	Case getCase(int x, int y);
	Case getCase(int caseID);
	std::vector<Piece*> getAlivePiece() const { return _alivePiece; }
	std::vector<Piece*> getAliveBlanc() const { return _aliveBlanc; }
	std::vector<Piece*> getAliveNoir() const { return _aliveNoir; }

	Couleur getMasterColor() const { return _masterColor; }

	void simuleMove(Piece* piece, Case caze);
	void undoSimileMove();

private:
	sf::RenderWindow* m_window;
	std::vector<Case> m_board;
	GameObjectManager* _gom;
	Couleur _masterColor;
	Son* _hitmarker;
	Trashbin* m_trash;
	Promote m_promote;

	std::vector<Piece*> _alivePiece;
	std::vector<Piece*> _aliveNoir;
	std::vector<Piece*> _aliveBlanc;

	//SimuleMove
	int s_oldCaseID;
	int s_newCaseID;
	Piece* s_pieceA;
	Piece* s_pieceB;
	//----------
};
