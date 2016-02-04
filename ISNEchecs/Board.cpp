#include "Board.h"

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
		setPiece(Piece(i + 9, Type::PION, Couleur::BLANC));
		setPiece(Piece(i + 49, Type::PION, Couleur::NOIR));
	}


	setPiece(Piece(1, Type::TOUR, Couleur::BLANC)); //Placement des tours
	setPiece(Piece(8, Type::TOUR, Couleur::BLANC));
	setPiece(Piece(57, Type::TOUR, Couleur::NOIR));
	setPiece(Piece(64, Type::TOUR, Couleur::NOIR));

	setPiece(Piece(2, Type::CAVALIER, Couleur::BLANC)); //Placement des cavaliers
	setPiece(Piece(7, Type::CAVALIER, Couleur::BLANC));
	setPiece(Piece(58, Type::CAVALIER, Couleur::NOIR));
	setPiece(Piece(63, Type::CAVALIER, Couleur::NOIR));

	setPiece(Piece(3, Type::FOU, Couleur::BLANC)); //Placement des fous
	setPiece(Piece(6, Type::FOU, Couleur::BLANC));
	setPiece(Piece(59, Type::FOU, Couleur::NOIR));
	setPiece(Piece(62, Type::FOU, Couleur::NOIR));

	setPiece(Piece(4, Type::ROI, Couleur::BLANC)); //Placement des rois/reines
	setPiece(Piece(5, Type::REINE, Couleur::BLANC));
	setPiece(Piece(60, Type::ROI, Couleur::NOIR));
	setPiece(Piece(61, Type::REINE, Couleur::NOIR));


}

Board::~Board()
{
}


void Board::setPiece(Piece piece)
{

	m_board.at(piece.getID()-1).setEmpty(0);
	m_board.at(piece.getID()-1).setPieceCase(piece);

}

void Board::movePiece(Piece piece, int ID)
{
	if (m_board.at(ID).isEmpty() == 1)
	{
		bool isPossible(int ID, int ID2, Type type, Couleur color);

		if (isPossible(piece.getID(), ID, piece.getType(), piece.getColor()) == true)
		{
			m_board.at(piece.getID()).setEmpty(1);
			m_board.at(piece.getID()).delPiece();
			piece.setID(ID);
			m_board.at(ID).setEmpty(0);
			m_board.at(ID).setPieceCase(piece);
		}
	}

	if (m_board.at(ID).getPiece().getColor() == piece.getColor())
	{
		;
	}
	else
	{
		; //PUT OLD PIECE IN TRASH (TODO)
	} 
}