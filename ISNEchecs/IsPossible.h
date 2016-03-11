#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Main\Board.h"

#include "Global.h"

inline bool Cavalier(Board *board, Piece piece, Case caze, Couleur color)
{
	if (piece.getID() + 6 == caze.getID() && piece.getID() % 8 != 0 && piece.getID() % 8 != 1)
	{
		return 1;
	}
	if (piece.getID() - 6 == caze.getID() && (piece.getID() + 1) % 8 != 0 && (piece.getID() + 1) % 8 != 7) // WTF
	{
		return 1;
	}
	if (piece.getID() + 10 == caze.getID() && (piece.getID() + 1) % 8 != 0 && (piece.getID() + 1) % 8 != 7)
	{
		return 1;
	}
	if (piece.getID() - 10 == caze.getID() && piece.getID() % 8 != 0 && piece.getID() % 8 != 1)
	{
		return 1;
	}
	if (piece.getID() + 15 == caze.getID() && piece.getID() % 8 != 0)
	{
		return 1;
	}
	if (piece.getID() - 15 == caze.getID() && (piece.getID() + 1) % 8 != 0)
	{
		return 1;
	}
	if (piece.getID() + 17 == caze.getID() && (piece.getID() + 1) % 8 != 0)
	{
		return 1;
	}
	if (piece.getID() - 17 == caze.getID() && piece.getID() % 8 != 0)
	{
		return 1;
	}
	return 0;
}

inline bool Tour(Board *board, Piece piece, Case caze, Couleur color)
{
	for (int i = 1; i < 9; i++)
	{
		if (piece.getID() + 7 < caze.getID())
		{
			if (piece.getID() + i * 8 == caze.getID())
			{
				if (caze.isEmpty())
					return 1;
				else
				{
					return 1;
				}
			}
			else if (piece.getID() + i * 8 > 63)
				return 0;
			else if (!board->getBoard().at(piece.getID() + i * 8).isEmpty())
				return 0;
		}

		if (piece.getID() > caze.getID() + 7)
		{
			if (piece.getID() - i * 8 == caze.getID())
			{
				return 1;
				
			}
			else if (piece.getID() - i * 8 < 0)
				return 0;
			else if (!board->getBoard().at(piece.getID() - i * 8).isEmpty())
				return 0;
		}

		if (caze.getID() < piece.getID())
		{

			if (caze.getID() >= div(piece.getID(), 8).quot * 8 && (div(piece.getID(), 8).quot + 1) * 8 - 1 >= caze.getID())
			{
				if (caze.getID() + i == piece.getID())
					return 1;
				else if (piece.getID() - i < 0)
					return 0;
				else if (!board->getBoard().at(piece.getID() - i).isEmpty())
					return 0;
			}

		}

		if (caze.getID() > piece.getID())
		{

			if (caze.getID() >= div(piece.getID(), 8).quot * 8 && ((div(piece.getID(), 8).quot + 1) * 8) - 1 >= caze.getID())
			{
				if (caze.getID() - i == piece.getID())
					return 1;
				else if (piece.getID() - i > 63)
					return 0;
				else if (!board->getBoard().at(piece.getID() + i).isEmpty())
					return 0;
			}
			else
				return 0;
		}

	}
	return 0;
}

inline bool Fou(Board *board, Piece piece, Case caze, Couleur color)
{
	int p = 0; //positif
	int n = 0; //negatif

	for (int i = 1; i < 9; i++)
	{
		if (caze.getID() > piece.getID())
		{
			for (int j = 1; j < 9; j++)
			{
				if (piece.getID() + j * 9 == caze.getID())
				{
					p++;
					break;
				}
				if (piece.getID() + j * 7 == caze.getID())
					std::cout << "bite" << std::endl;;
					break;
				if (piece.getID() + j * 9 > 63)
					return 0;
			}

			if (p > 0 && piece.getID() + i * 9 == caze.getID())
			{
				if (i <= 8 - (piece.getID()+1) % 8 && (piece.getID()+1) % 8 != 0)
				{
					return 1;
				}
				else
					return 0;
			}
			else if (p > 0 && piece.getID() + i * 9 < 63)
			{
				if (!board->getBoard().at(piece.getID() + i * 9).isEmpty() )
									return 0;
			}
				



			if (p == 0 && piece.getID() + i * 7 == caze.getID())
			{
				
				if (i <=  piece.getID() % 8) //depassement des bords (across the map)
				{
					return 1;
				}
				else
					return 0;

			}
			else if ( p==0 && piece.getID() + i * 7 < 63)
			{
				if (!board->getBoard().at(piece.getID() + i * 7).isEmpty())
					return 0;
			}
		}

		if (caze.getID() < piece.getID())
		{
			for (int j = 1; j < 9; j++)
			{
				if (piece.getID() - j * 9 == caze.getID())
				{
					n++;
					break;
				}
				if (piece.getID() - j * 7 == caze.getID())
					break;
				if (piece.getID() - (j * 7) < 0)
					return 0;
			}

			if (n > 0 && piece.getID() - i * 9 == caze.getID())
			{
				if (i <= piece.getID() % 8) //depassement des bords (across the map)
				{
					return 1;
				}
				else
					return 0;
			}
			else if (n > 0 && piece.getID() - i * 9 > 0)
			{
				if (!board->getBoard().at(piece.getID() - i * 9).isEmpty())
					return 0;
			}

			if (n == 0 && piece.getID() - i * 7 == caze.getID())
			{
				if (i <= piece.getID() % 8)
				{
					return 1;
				}
				else
					return 0;
			}
			else if (n ==0 && piece.getID() - i * 7 > 0)
			{
				if (!board->getBoard().at(piece.getID() - i * 7).isEmpty())
					return 0;
			}
		}
	}
	return 0;
}

inline bool Roi(Board *board, Piece piece, Case caze, Couleur color)
{
	if (board->getMasterColor() == NOIR && !piece.getHasMoved()) //to do si !echec
	{
		if (piece.getID() - 2 == caze.getID())
		{
			if (piece.getID() - 2 < 0)
				return 0;
			if (board->getBoard().at(piece.getID() - 1).isEmpty() && board->getBoard().at(piece.getID() - 2).isEmpty() && !board->getBoard().at(piece.getID() - 3).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
				return 1;
			else
				return 0;
		}

		if (piece.getID() + 2 == caze.getID())
		{
			if (piece.getID() + 2 > 63)
				return 0;
			if (board->getBoard().at(piece.getID() + 1).isEmpty() && board->getBoard().at(piece.getID() + 2).isEmpty() && board->getBoard().at(piece.getID() + 3).isEmpty() && !board->getBoard().at(piece.getID() + 4).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
				return 1;
			else
				return 0;
		}
	}

	if (board->getMasterColor() == BLANC && !piece.getHasMoved()) //to do si !echec
	{
		if (piece.getID() - 2 == caze.getID())
		{
			if (piece.getID() - 2 < 0)
				return 0;
			if (board->getBoard().at(piece.getID() - 1).isEmpty() && board->getBoard().at(piece.getID() - 2).isEmpty() && board->getBoard().at(piece.getID() - 3).isEmpty() && !board->getBoard().at(piece.getID() - 4).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
				return 1;
			else
				return 0;
		}

		if (piece.getID() + 2 == caze.getID())
		{
			if (piece.getID() + 2 > 63)
				return 0;
			if (board->getBoard().at(piece.getID() + 1).isEmpty() && board->getBoard().at(piece.getID() + 2).isEmpty() && !board->getBoard().at(piece.getID() + 3).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
				return 1;
			else
				return 0;
		}
	}

	if (piece.getID() + 1 == caze.getID() && (piece.getID()+1) % 8 != 0)
	{
		return 1;
	}

	if (piece.getID() - 1 == caze.getID() && (piece.getID()) % 8 != 0)
	{
		return 1;
	}

	if (piece.getID() + 8 == caze.getID())
	{
		return 1;
	}

	if (piece.getID() - 8 == caze.getID())
	{
		return 1;
	}

	if (piece.getID() + 7 == caze.getID() && (piece.getID()) % 8 != 0)
	{
		return 1;
	}

	if (piece.getID() - 7 == caze.getID() && (piece.getID() + 1) % 8 != 0)
	{
		return 1;
	}

	if (piece.getID() + 9 == caze.getID() && (piece.getID() + 1) % 8 != 0)
	{
		return 1;
	}

	if (piece.getID() - 9 == caze.getID() && (piece.getID()) % 8 != 0)
	{
		return 1;
	}

	return 0;
}

inline bool Pion(Board *board, Piece piece, Case caze, Couleur color)
{
	if (piece.getColor() == BLANC)
	{
		if (color == NOIR) //if noir en bas
		{
			if (piece.getID() + 16 == caze.getID() && !piece.getHasMoved())
			{
				return 1;
			}

			if (piece.getID() + 8 == caze.getID())
			{
				return 1;
			}

			if (piece.getID() + 7 == caze.getID() && piece.getID() % 8 != 0)
			{
				if (caze.getPiece()->getColor() != BLANC && caze.getPiece()->getColor() != NONEc)
					return 1;
				else
					return 0;
			}

			if (piece.getID() + 9 == caze.getID() && (piece.getID()+1) % 8 != 0)
			{
				if (caze.getPiece()->getColor() != BLANC && caze.getPiece()->getColor() != NONEc)
					return 1;
				else
					return 0;
			}
		}

		else if (color == BLANC)
		{
			if (piece.getID() - 16 == caze.getID() && !piece.getHasMoved())
			{
				return 1;
			}

			if (piece.getID() - 8 == caze.getID())
			{
				return 1;
			}

			if (piece.getID() - 7 == caze.getID() && (piece.getID()+1) % 8 != 0)
			{
				return 1;
			}

			if (piece.getID() - 9 == caze.getID() && piece.getID() % 8 != 0)
			{
				return 1;
			}
		}
		return 0;
	}

	if (piece.getColor() == NOIR)
	{
		if (color == NOIR)
		{
			if (piece.getID() - 16 == caze.getID() && !piece.getHasMoved())
			{
				return 1;
			}

			if (piece.getID() - 8 == caze.getID())
			{
				return 1;
			}

			if (piece.getID() - 7 == caze.getID() &&  (piece.getID()+1) % 8 != 0)
			{
				if (caze.getPiece()->getColor() != NOIR && caze.getPiece()->getColor() != NONEc)
					return 1;
				else
					return 0;
			}

			if (piece.getID() - 9 == caze.getID() && piece.getID() % 8 != 0)
			{
				if (caze.getPiece()->getColor() != NOIR && caze.getPiece()->getColor() != NONEc)
					return 1;
				else
					return 0;
			}
		}

		else if (color == BLANC)
		{
			if (piece.getID() + 16 == caze.getID() && !piece.getHasMoved())
			{
				return 1;
			}

			if (piece.getID() + 8 == caze.getID())
			{
				return 1;
			}

			if (piece.getID() + 7 == caze.getID() && piece.getID() % 8 != 0)
			{
				return 1;
			}

			if (piece.getID() + 9 == caze.getID() && (piece.getID()+1) % 8 != 0)
			{
				return 1;
			}
		}
		return 0;
	}
}

inline bool Reine(Board *board, Piece piece, Case caze, Couleur color)
{
	int vh = 0;
	int vb = 0;
	int hd = 0;
	int hg = 0;
	int dhd = 0;
	int dhg = 0;
	int dbd = 0;
	int dbg = 0;

	if (caze.getID() > piece.getID())
	{
		for (int j = 1; j < 9; j++)
		{
			if (piece.getID() + j * 8 == caze.getID())
			{
				vb = j;
				break;
			}

			if (piece.getID() + j * 9 == caze.getID())
			{
				dbd = j;
				break;
			}

			if (piece.getID() + j * 7 == caze.getID())
			{
				dbg = j;
				break;
			}

			if (ceil(caze.getID() / 8.0f) * 8 == floor(piece.getID() / 8.0f) * 8 + 8)
			{
				if (piece.getID() + j == caze.getID())
				{
					hd = j;
					break;
				}
			}
		}

		if (vb > 0)
		{
			if (vb > 1)
			{
				for (int i = 1; i < vb; i++)
				{
					if (!board->getBoard().at(piece.getID() + i * 8).isEmpty())
						return 0;
				}
			}
			return 1;
		}

		if (dbd > 0 && dbd <= 8 - (piece.getID() + 1) % 8 && (piece.getID() + 1) % 8 != 0)
		{
			if (dbd > 1)
			{
				for (int i = 1; i < dbd; i++)
				{
					if (!board->getBoard().at(piece.getID() + i * 9).isEmpty())
						return 0;
				}
			}
			return 1;
		}

		if (dbg > 0 && dbg <= piece.getID() % 8 )
		{
			if (dbg > 1)
			{
				for (int i = 1; i < dbg; i++)
				{
					if (!board->getBoard().at(piece.getID() + i * 7).isEmpty())
						return 0;
				}
			}
			return 1;
		}

		if (hd > 0)
		{
			if (hd > 1)
			{
				for (int i = 1; i < hd; i++)
				{
					if (!board->getBoard().at(piece.getID() + i).isEmpty())
						return 0;
				}
			}
			return 1;
		}
		return 0;
	}

	if (caze.getID() < piece.getID())
	{
		for (int j = 1; j < 9; j++)
		{
			if (piece.getID() - j * 8 == caze.getID())
			{
				vh = j;
				break;
			}

			if (piece.getID() - j * 9 == caze.getID())
			{
				dhg = j;
				break;
			}

			if (piece.getID() - j * 7 == caze.getID())
			{
				dhd = j;
				break;
			}

			if (floor(caze.getID() / 8) * 8 + 8 == ceil(piece.getID() / 8.0f) * 8)
			{
				if (piece.getID() - j == caze.getID())
				{
					hg = j;
					break;
				}
			}
		}

		if (vh > 0)
		{
			if (vh > 1)
			{
				for (int i = 1; i < vh; i++)
				{
					if (!board->getBoard().at(piece.getID() - i * 8).isEmpty())
						return 0;
				}
			}
			return 1;
		}
		if (dhg > 0 && dhg <= piece.getID() % 8)
		{
			if (dhg > 1)
			{
				for (int i = 1; i < dhg; i++)
				{
					if (!board->getBoard().at(piece.getID() - i * 9).isEmpty())
						return 0;
				}
			}
			return 1;
		}

		if (dhd > 0 && dhd <= 8 - (piece.getID() + 1) % 8 && (piece.getID()+1) % 8 != 0)
		{
			if (dhd > 1)
			{
				for (int i = 1; i < dhd; i++)
				{
					if (!board->getBoard().at(piece.getID() - i * 7).isEmpty())
						return 0;
				}
			}
			return 1;
		}

		if (hg > 0)
		{
			if (hg > 1)
			{
				for (int i = 1; i < vb; i++)
				{
					if (!board->getBoard().at(piece.getID() - i).isEmpty())
						return 0;
				}
			}
			return 1;
		}
		return 0;
	}
}

inline bool isPossible(Board *board, Piece piece, Case caze, Couleur color)
{
	switch (piece.getType())
	{
	case CAVALIER:
		return Cavalier(board, piece, caze, color);
		break;
	case TOUR:
		return Tour(board, piece, caze, color);
		break;
	case FOU:
		return Fou(board, piece, caze, color);
		break;
	case ROI:
		return Roi(board, piece, caze, color);
		break;
	case PION:
		return Pion(board, piece, caze, color);
		break;
	case REINE:
		return Reine(board, piece, caze, color);
		break;
	default:
		return 0;
		break;
	}
}