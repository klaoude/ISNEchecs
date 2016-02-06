#pragma once
#include "Main/PieceInfo.h"
#include <iostream>

inline bool isPossible(Board *board, Piece piece, Case caze)
{
	std::cout << piece.getID() << caze.getID() << piece.getType() << piece.getColor() << std::endl;
	if (piece.getType() == CAVALIER) //CAVALIER
	{
		if ((piece.getID() + 6 == caze.getID()) || (piece.getID() + 10 == caze.getID()) || (piece.getID() + 15 == caze.getID()) || (piece.getID() + 17 == caze.getID()))
			return 1;
		else
		{
			std::cout << "Denied" << std::endl;
			return 0;
		}
	}

	if (piece.getType() == TOUR) //TOUR
	{
		int s;
		int v;
		int h;
		for (size_t i = 0; i < 8; i++) 	//GET AXE DEPLACEMENT (S=1 -> vertical | S=0 -> Pas vertical, mais peut-etre diagonal)
		{
			if (caze.getID() == piece.getID() + i * 8 || caze.getID() == piece.getID() - i * 8)
				s++; 
		}
		
		if (s > 0) //SI DEPLACEMENT EST VERTICAL
		{
			if (caze.getID() - piece.getID() > 0) //Si le deplacement est vers le bas
			{
				for (size_t i = 0; i < 8; i++)
				{
					if (!board->getBoard.at(piece.getID() + i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard.at(piece.getID() + i * 8) == caze &&//si cette case est celle désirée
							board->getBoard.at(piece.getID() + i * 8).getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard.at(piece.getID() + i * 8).getColor() != piece.getColor())  // |
							return 1;
						else
							break;
					}
					else //Si la case est libre
						v++;

				}

				if (v > 0)
					return 1;
			}
			else //Si le deplacement est vers le haut
			{
				for (size_t i = 0; i < 8; i++)
				{
					if (!board->getBoard.at(piece.getID() - i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard.at(piece.getID() - i * 8) == caze &&//si cette case est celle désirée
							board->getBoard.at(piece.getID() - i * 8).getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard.at(piece.getID() - i * 8).getColor() != piece.getColor())  // |
							return 1;
						else
							break;
					}
					else //Si la case est libre
						v++;
			}
		}


		if (s == 0 && floor(piece.getID() / 8) * 8 < caze.getID() && caze.getID() < ceil(piece.getID() / 8) * 8) //SI DEPLACEMENT EST HORIZONTAL
		{

		}




	}

	if (piece.getType() == FOU) //FOU
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{
			if (board->getBoard().at(piece.getID() + i * 8).isEmpty())
			{
				if (board->getBoard().at(piece.getID() + i * 9).getID() == caze.getID() && 
					board->getBoard().at(piece.getID() + i * 9).getPiece()->getColor() != Couleur::NONEc && 
					board->getBoard().at(piece.getID() + i * 9).getPiece()->getColor() != piece.getColor())
					m++;
				else
					break;
			}

			if ((piece.getID() + i * 9 == caze.getID()) || (piece.getID() - i * 9 == caze.getID()) || (piece.getID() + i * 7 == caze.getID()) || (piece.getID() - i * 7 == caze.getID()))
				m++;
			else
				m = m;
		}
		if (m > 1)
			return 1;
		else
		{
			std::cout << "Denied" << std::endl;
			return 0;
		}
	}

	if (piece.getType() == ROI) //ROI
	{
		if ((piece.getID() + 1 == caze.getID()) || (piece.getID() - 1 == caze.getID()) || (piece.getID() + 8 == caze.getID()) || (piece.getID() - 8 == caze.getID()) || (piece.getID() + 9 == caze.getID()) || (piece.getID() - 9 == caze.getID()) || (piece.getID() + 7 == caze.getID()) || (piece.getID() - 7 == caze.getID()))
			return 1;
		else
			return 0;
	}

	if (piece.getType() == PION) //PION
	{
		if (piece.getColor() == BLANC)
		{
			if (piece.getID() + 8 == caze.getID())
				return 1;
			else
			{
				std::cout << "Denied" << std::endl;
				return 0;
			}
		}

		if (piece.getColor() == NOIR)
		{
			if (piece.getID() - 8 == caze.getID())
				return 1;
			else
			{
				std::cout << "Denied" << std::endl;
				return 0;
			}
		}
	}

	if (piece.getType() == REINE) //REINE
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{
			if ((piece.getID() + i * 9 == caze.getID()) || (piece.getID() - i * 9 == caze.getID()) || (piece.getID() + i * 8 == caze.getID()) || (piece.getID() - i * 8 == caze.getID()) || (piece.getID() + i * 7 == caze.getID()) || (piece.getID() - i * 7 == caze.getID()))
				m++;
			else
				m = m;
		}
		if (m > 0)
			return 1;
		else
		{
			std::cout << "Denied" << std::endl;
			return 0;
		}
	}
	return 0;
}