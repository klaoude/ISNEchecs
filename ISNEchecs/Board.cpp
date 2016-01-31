#include "Board.h"
#include "Case.h"
#include "Piece.h"
#include "CaseID.h"

Board::Board()
{
	int x=0;
	int y=0;

	for (size_t i = 0; i < 64; i++) // on place les cases
	{
		if (i % 8 == 0 && i != 0)
		{
			y += 100;
			x = 0;
		}


		m_board.push_back(Case(x, y));
		x += 100;
	}

	for (int i = 0; i < 8; i++) //Placement des pions
	{
		m_board.at(i+8).setPiece(Piece(PION, BLANC));
		m_board.at(i+48).setPiece(Piece(PION, NOIR));

	}

	m_board.at(0).setPiece(Piece(TOUR, BLANC));
	m_board.at(7).setPiece(Piece(TOUR, BLANC));
	m_board.at(56).setPiece(Piece(TOUR, NOIR));
	m_board.at(63).setPiece(Piece(TOUR, NOIR));

	m_board.at(1).setPiece(Piece(CAVALIER, BLANC));
	m_board.at(6).setPiece(Piece(CAVALIER, BLANC));
	m_board.at(57).setPiece(Piece(CAVALIER, NOIR));
	m_board.at(62).setPiece(Piece(CAVALIER, NOIR));

	m_board.at(2).setPiece(Piece(FOU, BLANC));
	m_board.at(5).setPiece(Piece(FOU, BLANC));
	m_board.at(58).setPiece(Piece(FOU, NOIR));
	m_board.at(61).setPiece(Piece(FOU, NOIR));

	m_board.at(3).setPiece(Piece(ROI, BLANC));
	m_board.at(4).setPiece(Piece(REINE, BLANC));
	m_board.at(59).setPiece(Piece(ROI, NOIR));
	m_board.at(60).setPiece(Piece(REINE, NOIR));

}


Board::~Board()
{
}

Case Board::getCase(int ID)
{
	return m_board.at(ID - 1);
}

void Board::getPiece(int ID)
{
	std::cout << m_board.at(ID - 1).getPiece().getType() << " " << m_board.at(ID - 1).getPiece().getColor() << std::endl;
}