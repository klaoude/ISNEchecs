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
	float x, y;
	if (textureSize.x != 0 && textureSize.y != 0)
	{
		switch (code)
		{
		case 1:
			x = BOARD_SIZE / (float)textureSize.x;
			y = BOARD_SIZE / (float)textureSize.y;
			break;
		case 2:
			x = PIECE_SIZE / (float)textureSize.x;
			y = PIECE_SIZE / (float)textureSize.y;
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
		for (int i = 1; i < 9; i++)
		{
			if (piece.getID() + 7 < caze.getID())
			{
				if (piece.getID() + i * 8 == caze.getID())
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
						else
							return 0;
					}
				}
				else if (!board->getBoard().at(piece.getID() + i * 8).isEmpty())
					return 0;
			}



			if (piece.getID() > caze.getID() + 7)
			{
				if (piece.getID() - i * 8 == caze.getID())
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
						else
							return 0;
					}
				}
				else if (!board->getBoard().at(piece.getID() - i * 8).isEmpty())
					return 0;
			}

			if (caze.getID() < piece.getID())
			{

				if (floor(caze.getID() / 8)*8 + 8 == ceil(piece.getID()/8.0f)*8)
				{
					if (piece.getID() - i == caze.getID())
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
							else
								return 0;
						}
					}
					else if (!board->getBoard().at(piece.getID() - i).isEmpty())
						return 0;
				}
			}
			if (caze.getID() > piece.getID())
			{

				if (ceil(caze.getID() / 8.0f) * 8  == floor(piece.getID() / 8.0f) * 8 + 8)
				{
					if (piece.getID() + i == caze.getID())
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
							else
								return 0;
						}
					}
					else if (!board->getBoard().at(piece.getID() + i).isEmpty())
						return 0;
				}
			}

		}
		
	}



	

	if (piece.getType() == FOU) //FOU
	{
		int p = 0;
		int n = 0;
		for (int i = 1; i < 9; i++)
		{
			if (caze.getID() > piece.getID())
			{

				for (size_t j = 1; j < 9; j++)
				{
					if (piece.getID() + j * 9 == caze.getID())
						p++ ;
				}

				if (p > 0 && piece.getID() + i * 9 == caze.getID())
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
				else if (p>0 && !board->getBoard().at(piece.getID() + i * 9).isEmpty())
					return 0;

				if (p == 0 && piece.getID() + i * 7 == caze.getID())
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
				else if (p==0 && !board->getBoard().at(piece.getID() + i * 7).isEmpty())
					return 0;

			}
			
			if (caze.getID() < piece.getID())
			{
				for (size_t j = 1; j < 9; j++)
				{
					if (piece.getID() - j * 9 == caze.getID())
						n++;
				}

				if (n > 0 && piece.getID() - i * 9 == caze.getID())
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
				else if (n>0 && !board->getBoard().at(piece.getID() - i * 9).isEmpty())
					return 0;
			
				if (n == 0 && piece.getID() - i * 7 == caze.getID())
				{
					if (caze.isEmpty())
					{
						return 1;
					}
					else if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
				else if (n==0 && !board->getBoard().at(piece.getID() - i * 7).isEmpty())
					return 0;
			}
			
		}

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
					return 0;
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
				return 0;
		}

		if (piece.getColor() == NOIR)
		{
			if (piece.getID() - 8 == caze.getID())
			{
				if (caze.isEmpty())
					return 1;
				else
					return 0;
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
				return 0;
		}
	}

	if (piece.getType() == REINE) //REINE
	{
		int p = 0;
		int n = 0;
		for (int i = 1; i < 9; i++)
		{
			if (caze.getID() > piece.getID())
			{

				for (size_t j = 1; j < 9; j++)
				{
					if (piece.getID() + j * 9 == caze.getID())
						p++;
				}

				if (p > 0 && piece.getID() + i * 9 == caze.getID())
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
				else if (p>0 && !board->getBoard().at(piece.getID() + i * 9).isEmpty())
					return 0;

				if (p == 0 && piece.getID() + i * 7 == caze.getID())
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
				else if (p == 0 && !board->getBoard().at(piece.getID() + i * 7).isEmpty())//i,ophumilbm
					return 0;

			}

			if (caze.getID() < piece.getID())
			{
				for (size_t j = 1; j < 9; j++)
				{
					if (piece.getID() - j * 9 == caze.getID())
						n++;
				}

				if (n > 0 && piece.getID() - i * 9 == caze.getID())
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
				else if (n>0 && !board->getBoard().at(piece.getID() - i * 9).isEmpty())
					return 0;

				if (n == 0 && piece.getID() - i * 7 == caze.getID())
				{
					if (caze.isEmpty())
					{
						return 1;
					}
					else if ((caze.getPiece()->getColor() != piece.getColor()) &&
						(caze.getPiece()->getColor() != NONEc))
						return 1;
				}
				else if (n == 0 && !board->getBoard().at(piece.getID() - i * 7).isEmpty())
					return 0;
			}

		}
		for (int i = 1; i < 9; i++)
		{
			if (piece.getID() + 7 < caze.getID())
			{
				if (piece.getID() + i * 8 == caze.getID())
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
						else
							return 0;
					}
				}
				else if (!board->getBoard().at(piece.getID() + i * 8).isEmpty())
					return 0;
			}



			if (piece.getID() > caze.getID() + 7)
			{
				if (piece.getID() - i * 8 == caze.getID())
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
						else
							return 0;
					}
				}
				else if (!board->getBoard().at(piece.getID() - i * 8).isEmpty())
					return 0;
			}

			if (caze.getID() < piece.getID())
			{

				if (floor(caze.getID() / 8) * 8 + 8 == ceil(piece.getID() / 8.0f) * 8)
				{
					if (piece.getID() - i == caze.getID())
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
							else
								return 0;
						}
					}
					else if (!board->getBoard().at(piece.getID() - i).isEmpty())
						return 0;
				}
			}
			if (caze.getID() > piece.getID())
			{

				if (ceil(caze.getID() / 8.0f) * 8 == floor(piece.getID() / 8.0f) * 8 + 8)
				{
					if (piece.getID() + i == caze.getID())
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
							else
								return 0;
						}
					}
					else if (!board->getBoard().at(piece.getID() + i).isEmpty())
						return 0;
				}
			}

		}
	}
}