#include "Board.h"
#include "Case.h"
#include "Piece.h"
#include "PieceInfo.h"



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
		setPiece(i + 9, Type::PION, Couleur::BLANC);
		setPiece(i + 49, Type::PION, Couleur::NOIR);
	}

	setPiece(1, Type::TOUR, Couleur::BLANC); //Placement des tours
	setPiece(8, Type::TOUR, Couleur::BLANC);
	setPiece(57, Type::TOUR, Couleur::NOIR);
	setPiece(64, Type::TOUR, Couleur::NOIR);

	setPiece(2, Type::CAVALIER, Couleur::BLANC); //Placement des cavaliers
	setPiece(7, Type::CAVALIER, Couleur::BLANC);
	setPiece(58, Type::CAVALIER, Couleur::NOIR);
	setPiece(63, Type::CAVALIER, Couleur::NOIR);

	setPiece(3, Type::FOU, Couleur::BLANC); //Placement des fous
	setPiece(6, Type::FOU, Couleur::BLANC);
	setPiece(59, Type::FOU, Couleur::NOIR);
	setPiece(62, Type::FOU, Couleur::NOIR);

	setPiece(4, Type::ROI, Couleur::BLANC); //Placement des rois/reines
	setPiece(5, Type::REINE, Couleur::BLANC);
	setPiece(60, Type::ROI, Couleur::NOIR);
	setPiece(61, Type::REINE, Couleur::NOIR);
}


Board::~Board()
{
}


void Board::setPiece(int ID, Type type, Couleur color)
{
	m_board.at(ID).setEmpty(0);
	m_board.at(ID).setPieceCase(type, color, ID);
}


void Board::movePiece(Piece piece, int ID)
{
	if (m_board.at(ID).isEmpty() == 1)
	{
		bool isPossible(int ID, int ID2, Type type, Couleur color);

		if (isPossible(piece.getID(), ID, piece.getType(), piece.getColor()) == true)
		{
			m_board.at(piece.getID()).setEmpty(1);
			m_board.at(piece.getID()).setPieceCase(Type::NONEt, Couleur::NONEc,NULL);
			piece.setID(ID);
			m_board.at(ID).setEmpty(0);
			m_board.at(ID).setPieceCase(piece.getType(), piece.getColor(), piece.getID());
		}
	}

	if (m_board.at(ID).getPiece().getColor() == piece.getColor())
	{
		;
	}
	if (m_board.at(ID).getPiece().getColor() != piece.getColor())
	{
		; //PUT OLD PIECE IN TRASH (TODO)
	} 
}