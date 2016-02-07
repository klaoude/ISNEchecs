#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Global.h"

inline void setScale(GameObject* go, int code)
{
	/*
	Code : 1 = Board
		   2 = Piece
	*/
	sf::Vector2u textureSize = go->getTextureSize();
	int x, y;
	if (textureSize.x != 0 && textureSize.y != 0)
	{
		switch (code)
		{
		case 1:
			x = BOARD_SIZE / textureSize.x;
			y = BOARD_SIZE / textureSize.y;
			break;
		case 2:
			x = PIECE_SIZE / textureSize.x;
			y = PIECE_SIZE / textureSize.y;
			break;
		}
		
	}
	else 
	{
		x = 1;
		y = 1;
	}
	go->scale(x, y);
}

inline bool isPossible(Board *board, Piece piece, Case caze)
{
	std::cout << piece.getID() << caze.getID() << piece.getType() << piece.getColor() << std::endl;
	if (piece.getType() == CAVALIER) //CAVALIER
	{
		if (piece.getID() + 6== caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 6 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 10 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 10 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 15 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 15 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 17 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 17 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		return 0;
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
					if (! board->getBoard().at(piece.getID() + i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard().at(piece.getID() + i * 8).getID() == caze.getID() && //si cette case est celle désirée
							board->getBoard().at(piece.getID() + i * 8).getPiece()->getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard().at(piece.getID() + i * 8).getPiece()->getColor() != piece.getColor())  // |
							return 1;
						else
							v = 0;
							break;
					}
					else //Si la case est libre
						v++;

				}
			}
			else //Si le deplacement est vers le haut
			{
				for (size_t i = 0; i < 8; i++)
				{
					if (!board->getBoard().at(piece.getID() - i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard().at(piece.getID() - i * 8).getID() == caze.getID() &&//si cette case est celle désirée
							board->getBoard().at(piece.getID() - i * 8).getPiece()->getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard().at(piece.getID() - i * 8).getPiece()->getColor() != piece.getColor())  // |
							return 1;
						else
							v = 0;
							break;
					}
					else //Si la case est libre
						v++;
				}
			}
		}

		if (s == 0 && floor(piece.getID() / 8) * 8 < caze.getID() && caze.getID() < ceil(piece.getID() / 8) * 8) //SI DEPLACEMENT EST HORIZONTAL
		{
			int d = piece.getID() - caze.getID();
			if (d < 0) //Si le deplacement est vers la droite
			{
				for (size_t i = -1; i >d+1; i--)
				{
					if (!board->getBoard().at(piece.getID() + i).isEmpty())
					{
						h = 0;
						break;
					}
					else
						h++;
				}
			}

			if (d > 0) //Si le deplacement est vers la gauche
			{
				for (size_t i = 1; i < d - 1; i++)
				{
					if (!board->getBoard().at(piece.getID() - i).isEmpty())
					{
						h = 0;
						break;
					}
					else
						h++;
				}
			}

			if (h > 0)
				return 1;
			else if (v > 0)
				return 1;
			else
				return 0;
		}
	}





	if (piece.getType() == FOU) //FOU
	{
		for (int i = 1; i < 9; i++)
		{

			if (piece.getID() + i * 9 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() - i * 9 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() + i * 7 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() - i * 7 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
			}
		}
		return 0;

	}

	if (piece.getType() == ROI) //ROI
	{
		if (piece.getID() + 1 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 1 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 8 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 8 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 7 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 7 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() + 9 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		if (piece.getID() - 9 == caze.getID())
		{
			if (caze.isEmpty())
				return 1;
			else if ((caze.getPiece()->getColor() != piece.getColor()) &&
				(caze.getPiece()->getColor() != NONEc))
				return 1;
		}
		return 0;
	}

	if (piece.getType() == PION) //PION
	{
		if (piece.getColor() == BLANC)
		{
			if (piece.getID() + 8 == caze.getID())
			{
				if (caze.isEmpty())
					return 1;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
			if (piece.getID() + 7 == caze.getID())
			{
				if (caze.isEmpty())
					return 0;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
			if (piece.getID() + 9 == caze.getID())
			{
				if (caze.isEmpty())
					return 0;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
		}

		if (piece.getColor() == NOIR)
		{
			if (piece.getID() - 8 == caze.getID())
			{
				if (caze.isEmpty())
					return 1;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
			if (piece.getID() - 7 == caze.getID())
			{
				if (caze.isEmpty())
					return 0;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
			if (piece.getID() - 9 == caze.getID())
			{
				if (caze.isEmpty())
					return 0;
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
					else
						return 0;
				}
			}
		}
	}

	if (piece.getType() == REINE) //REINE
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
					if (!board->getBoard().at(piece.getID() + i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard().at(piece.getID() + i * 8).getID() == caze.getID() && //si cette case est celle désirée
							board->getBoard().at(piece.getID() + i * 8).getPiece()->getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard().at(piece.getID() + i * 8).getPiece()->getColor() != piece.getColor())  // |
							return 1;
						else
							v = 0;
						break;
					}
					else //Si la case est libre
						v++;

				}
			}
			else //Si le deplacement est vers le haut
			{
				for (size_t i = 0; i < 8; i++)
				{
					if (!board->getBoard().at(piece.getID() - i * 8).isEmpty()) //Si la case est prise
					{
						if (board->getBoard().at(piece.getID() - i * 8).getID() == caze.getID() &&//si cette case est celle désirée
							board->getBoard().at(piece.getID() - i * 8).getPiece()->getColor() != Couleur::NONEc && //  |Si la piece sur la case est de l'autre couleur
							board->getBoard().at(piece.getID() - i * 8).getPiece()->getColor() != piece.getColor())  // |
							return 1;
						else
							v = 0;
						break;
					}
					else //Si la case est libre
						v++;
				}
			}
		}

		if (s == 0 && floor(piece.getID() / 8) * 8 < caze.getID() && caze.getID() < ceil(piece.getID() / 8) * 8) //SI DEPLACEMENT EST HORIZONTAL
		{
			int d;
			d = piece.getID() - caze.getID();
			if (d < 0) //Si le deplacement est vers la droite
			{
				for (size_t i = 1; i < d - 1; i++)
				{
					if (!board->getBoard().at(piece.getID() + i).isEmpty())
					{
						h = 0;
						break;
					}
					else
						h++;
				}
			}

			if (d > 0) //Si le deplacement est vers la gauche
			{
				for (size_t i = 1; i < d - 1; i++)
				{
					if (!board->getBoard().at(piece.getID() - i).isEmpty())
					{
						h = 0;
						break;
					}
					else
						h++;
				}
			}

			if (h > 0)
				return 1;
			else if (v > 0)
				return 1;
			else
				return 0;
		}

		for (int i = 1; i < 9; i++)
		{

			if (piece.getID() + i * 9 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() - i * 9 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() + i * 7 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else
				{
					if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
			}
			if (piece.getID() - i * 7 == caze.getID())
			{
				if (caze.isEmpty())
				{
					return 1;
				}
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
			}
		}
		return 0;

	}
	return 0;
}