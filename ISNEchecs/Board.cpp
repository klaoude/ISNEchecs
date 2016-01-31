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


		m_board.push_back(Case(x, y, i+1));
		x += 100;
	}

	for (int i = 0; i < 8; i++) //Placement des pions
	{
		m_board.at(i+8).setPiece(Piece(PION, BLANC,i+8));
		m_board.at(i+48).setPiece(Piece(PION, NOIR,i+48));

	}

	m_board.at(0).setPiece(Piece(TOUR, BLANC,1));
	m_board.at(7).setPiece(Piece(TOUR, BLANC,8));
	m_board.at(56).setPiece(Piece(TOUR, NOIR,57));
	m_board.at(63).setPiece(Piece(TOUR, NOIR,64));

	m_board.at(1).setPiece(Piece(CAVALIER, BLANC,2));
	m_board.at(6).setPiece(Piece(CAVALIER, BLANC,7));
	m_board.at(57).setPiece(Piece(CAVALIER, NOIR,58));
	m_board.at(62).setPiece(Piece(CAVALIER, NOIR,63));

	m_board.at(2).setPiece(Piece(FOU, BLANC,3));
	m_board.at(5).setPiece(Piece(FOU, BLANC,6));
	m_board.at(58).setPiece(Piece(FOU, NOIR,59));
	m_board.at(61).setPiece(Piece(FOU, NOIR,62));

	m_board.at(3).setPiece(Piece(ROI, BLANC,4));
	m_board.at(4).setPiece(Piece(REINE, BLANC,5));
	m_board.at(59).setPiece(Piece(ROI, NOIR,60));
	m_board.at(60).setPiece(Piece(REINE, NOIR,61));

}


Board::~Board()
{
}

Case Board::getCase(int ID)
{
	return m_board.at(ID - 1);
}

void Board::getTyCo(int ID)
{
	std::cout << m_board.at(ID - 1).getPiece().getType() << " " << m_board.at(ID - 1).getPiece().getColor() << std::endl;
}