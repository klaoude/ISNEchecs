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
				else if (piece.getID() + i * 8 > 63)
					return 0;
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
				else if (piece.getID() - i * 8 < 0)
					return 0;
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
					else if (piece.getID() - i < 0)
						return 0;
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
					if (piece.getID() + i > 63)
						return 0;
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

				for (int j = 1; j < 9; j++)
				{
					if (piece.getID() + j * 9 == caze.getID())
					{
						p++;
						break;
					}
					if (piece.getID() + j * 7 == caze.getID())
					{
						break;
					}
					if (piece.getID() + j * 9 > 63)
						return 0;
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
				else if (p == 0 && !board->getBoard().at(piece.getID() + i * 7).isEmpty())
					return 0;

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
					{
						break;
					}
					if (piece.getID() - (j * 7) < 0)
						return 0;
					if (piece.getID() - (j * 7) < 0)
						return 0;
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
				if (!(-i*7 < 0))
					if (n==0 && !board->getBoard().at(piece.getID() - i * 7).isEmpty()) //
						return 0;
			}
			
		}

	}

	if (piece.getType() == ROI) //ROI
	{
		
		if (piece.getColor() ==  BLANC && !piece.getHasMoved()) //to do si !echec
		{
			if (piece.getID() - 2 == caze.getID()) 
			{
				if (piece.getID() - 2 < 0)
					return 0;
				if (board->getBoard().at(piece.getID()-1).isEmpty() && board->getBoard().at(piece.getID()-2).isEmpty() && !board->getBoard().at(piece.getID()-3).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
					return 1;
				else
					return 0;
			}
			
			if (piece.getID() + 2 == caze.getID())
			{
				if (piece.getID() + 2 > 63)
					return 0;
				if (board->getBoard().at(piece.getID()+1).isEmpty() && board->getBoard().at(piece.getID()+2).isEmpty() && board->getBoard().at(piece.getID()+3).isEmpty() && !board->getBoard().at(piece.getID()+7).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
					return 1;
				else
					return 0;
			}
			
		}
		if (piece.getColor() ==  NOIR && !piece.getHasMoved()) //to do si !echec
		{
			if (piece.getID() - 2 == caze.getID()) 
			{
				if (piece.getID() - 2 < 0)
					return 0;
				if (board->getBoard().at(piece.getID()-1).isEmpty() && board->getBoard().at(piece.getID()-2).isEmpty() && !board->getBoard().at(piece.getID()-3).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
					return 1;
				else
					return 0;
			}
			
			if (piece.getID() + 2 == caze.getID())
			{
				if (piece.getID() + 2 > 63)
					return 0;
				if (board->getBoard().at(piece.getID()+1).isEmpty() && board->getBoard().at(piece.getID()+2).isEmpty() && board->getBoard().at(piece.getID()+3).isEmpty() && !board->getBoard().at(piece.getID()+7).getPiece()->getHasMoved()) //si cases sont libres et les tour/roi hasn't moved
					return 1;
				else
					return 0;
			}
			
		}
		
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
			if (piece.getID() + 16 == caze.getID() && !piece.getHasMoved())
			{
				if (caze.isEmpty())
					return 1;
				else
					return 0;
			}
			
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
			if (piece.getID() - 16 == caze.getID() && !piece.getHasMoved())
			{
				if (caze.isEmpty())
					return 1;
				else
					return 0;
			}
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
				if (ceil(caze.getID() / 8.0f) * 8  == floor(piece.getID() / 8.0f) * 8 + 8)
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
				if (board->getBoard().at(piece.getID() + vb * 8).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
			}

			if (dbd > 0)
			{
				if (dbd > 1)
				{
					for (int i = 1; i < dbd; i++)
					{
						if (!board->getBoard().at(piece.getID() + i * 9).isEmpty())
							return 0;
					}
				}
				if (board->getBoard().at(piece.getID() + dbd * 9).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
			}

			if (dbg > 0)
			{
				if (dbg > 1)
				{
					for (int i = 1; i < dbg; i++)
					{
						if (!board->getBoard().at(piece.getID() + i * 7).isEmpty())
							return 0;
					}
				}
				if (board->getBoard().at(piece.getID() + dbg * 7).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
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
				if (board->getBoard().at(piece.getID() + hd).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
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
				if (board->getBoard().at(piece.getID() - vh * 8).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
			}
			if (dhg > 0)
			{
				if (dhg > 1)
				{
					for (int i = 1; i < dhg; i++)
					{
						if (!board->getBoard().at(piece.getID() - i * 9).isEmpty())
							return 0;
					}
				}
				if (board->getBoard().at(piece.getID() - dhg * 9).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
			}
			if (dhd > 0)
			{
				if (dhd > 1)
				{
					for (int i = 1; i < dhd; i++)
					{
						if (!board->getBoard().at(piece.getID() - i * 7).isEmpty())
							return 0;
					}
				}
				if (board->getBoard().at(piece.getID() - dhd * 7).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
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
				if (board->getBoard().at(piece.getID() - hg).isEmpty())
					return 1;
				else if ((caze.getPiece()->getColor() != piece.getColor()) &&
					(caze.getPiece()->getColor() != NONEc))
					return 1;
				else
					return 0;
			}
			return 0;

		}
	}
	return 0;
}

int findroinoir(Board* board)
{
	for (int i = 0; i < 64; i++)
	{
		if (board->getBoard().at(i).getPiece()->getType() == ROI && board->getBoard().at(i).getPiece()->getColor() == NOIR)
			return 1;
	}
}

int findroiblanc(Board* board)
{
	for (int i = 0; i < 64; i++)
	{
		if (board->getBoard().at(i).getPiece()->getType() == ROI && board->getBoard().at(i).getPiece()->getColor() == BLANC)
			return i;
	}
}

bool echec(Board* board, int ID)
{
	for (int i = 0; i < 64; i++)
	{
		if (isPossible(board, *board->getBoard().at(i).getPiece(), board->getBoard().at(ID)))
			return 1;
	}
	return 0;
}

int echec(Board* board)
{
	//0 -> rien | 1 -> blanc  | 2 -> noir | 3 -> les deux
	// 4 -> blanc mat | 5 -> noir mat
	int be = 0;
	int ne = 0;
	int bem = 0;
	int nem = 0;
	std::vector<int> blanc;
	std::vector<int> noir;

	if (findroiblanc(board)+ 1 < 64 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)+ 1)))
		blanc.push_back(1);
	if (findroiblanc(board)+ 9 < 64 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)+ 9)))
		blanc.push_back(9);
	if (findroiblanc(board)+ 8 < 64 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)+ 8)))
		blanc.push_back(8);
	if (findroiblanc(board)+ 7 < 64 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)+ 7)))
		blanc.push_back(7);
	if (findroiblanc(board)- 1 > -1 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)- 1)))
		blanc.push_back(-1);
	if (findroiblanc(board)- 9 > -1 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)- 9)))
		blanc.push_back(-9);
	if (findroiblanc(board)- 8 > -1 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)- 8)))
		blanc.push_back(-8);
	if (findroiblanc(board)- 7 > -1 && isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board)- 7)))
		blanc.push_back(-7);

	if (findroinoir(board)+ 1 < 64 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)+ 1)))
		noir.push_back(1);
	if (findroinoir(board)+ 9 < 64 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)+ 9)))
		noir.push_back(9);
	if (findroinoir(board)+ 8 < 64 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)+ 8)))
		noir.push_back(8);
	if (findroinoir(board)+ 7 < 64 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)+ 7)))
		noir.push_back(7);
	if (findroinoir(board)- 1 > -1 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)- 1)))
		noir.push_back(-1);
	if (findroinoir(board)- 9 > -1 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)- 9)))
		noir.push_back(-9);
	if (findroinoir(board)- 8 > -1 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)- 8)))
		noir.push_back(-8);
	if (findroinoir(board)- 7 > -1 && isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board)- 7)))
		noir.push_back(-7);


	for (int i = 0; i < 64; i++)
	{
		if (isPossible(board, *board->getBoard().at(i).getPiece(), board->getBoard().at(findroiblanc(board))))
			be++;
		if (isPossible(board, *board->getBoard().at(i).getPiece(), board->getBoard().at(findroinoir(board))))
			ne++;
	}
	
	if (be > 0)
	{
		/*for (int i = 0; i < blanc.size(); i++)
		{
			if (echec(board, blanc[i]) == 1)
				bem++;
		}*/
		if (bem == 0)
			return 4;
		else 
			return 1;
	}
	if (ne > 0)
	{
		/*for (int i = 0; i < noir.size(); i++)
		{
			if (echec(board, noir[i]) == 1)
				nem++;
		}*/
		if (nem == 0)
			return 5;
		else
			return 2;
	}
	return 0;

}

