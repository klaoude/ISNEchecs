#include "Piece.h"
#include "CaseID.h"
#include "Board.h"

Piece::Piece(Type type, Couleur color, int ID) : m_case(0, 0, 0)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
	//m_case = ;
}


Piece::~Piece()
{
}

void Piece::setType(Type type)
{
	m_type = type;
}


void Piece::setColor(Couleur couleur)
{
	m_color = couleur;
}


/*
void Piece::move(Board* board, int ID)
{
	if (m_type == Type::PION)
	{
		if (m_ID + 8 == ID)
		{
			if (board->getBoard().at(ID).isEmpty() == 1 ) //si la case est libre
			{
				board->getBoard().at(m_ID).delPiece(); //del la piece de la case
				board->getBoard().at(m_ID).setEmpty(1); //rend la case libre
				m_ID == ID; //set le nouvel ID de la piece
				board->getBoard().at(m_ID).setPiece(*this); //deplace le pion
				board->getBoard().at(ID).setEmpty(0); //rend la nouvelle case prise
			}

			if (board->getBoard().at(ID).isEmpty() == 0 && board->getBoard().at(ID).getPiece().getColor() != NONE && board->getBoard().at(ID).getPiece().getColor() != board->getBoard().at(m_ID).getPiece().getColor()) // si la case est prise par une piece de couleur différente
			{
				board->getBoard().at(m_ID).delPiece(); //del la piece de la case
				board->getBoard().at(m_ID).setEmpty(1); //rend la case libre

				board->getBoard().at(ID).delPiece(); //del la piece ennemie de la case

				m_ID == ID; //set le nouvel ID de la piece
				board->getBoard().at(m_ID).setPiece(this); //deplace le pion
				board->getBoard().at(ID).setEmpty(0); //rend la nouvelle case prise
			}

			if (board->getBoard().at(ID).isEmpty() == 0 && board->getBoard().at(ID).getPiece().getColor() == board->getBoard().at(m_ID).getPiece().getColor())
				;
		}
	}
}
*/