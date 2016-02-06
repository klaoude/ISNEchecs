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

inline bool isPossible(Piece piece, int ID2)
{
	std::cout << piece.getID() << ID2 << piece.getType() << piece.getColor() << std::endl;
	if (piece.getType() == CAVALIER) //CAVALIER
	{
		if ((piece.getID() + 6 == ID2) || (piece.getID() + 10 == ID2) || (piece.getID() + 15 == ID2) || (piece.getID() + 17 == ID2))
			return 1;
		else
		{
			std::cout << "Denied" << std::endl;
			return 0;
		}
	}

	if (piece.getType() == TOUR) //TOUR
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{



			if ((piece.getID() + i * 8 == ID2) || (piece.getID() - i * 8 == ID2))
				m++;
			if (floor(piece.getID() / 8) * 8 <= ID2 && ID2 < ceil(piece.getID() / 8) * 8)
				m++;
			else
				;
		}
		if (m > 1)
			return 1;
		else
		{
			std::cout << "Denied" << std::endl;
			return 0;
		}

	}

	if (piece.getType() == FOU) //FOU
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{
			if ((piece.getID() + i * 9 == ID2) || (piece.getID() - i * 9 == ID2) || (piece.getID() + i * 7 == ID2) || (piece.getID() - i * 7 == ID2))
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
		if ((piece.getID() + 1 == ID2) || (piece.getID() - 1 == ID2) || (piece.getID() + 8 == ID2) || (piece.getID() - 8 == ID2) || (piece.getID() + 9 == ID2) || (piece.getID() - 9 == ID2) || (piece.getID() + 7 == ID2) || (piece.getID() - 7 == ID2))
			return 1;
		else
			return 0;
	}

	if (piece.getType() == PION) //PION
	{
		if (piece.getColor() == BLANC)
		{
			if (piece.getID() + 8 == ID2)
				return 1;
			else
			{
				std::cout << "Denied" << std::endl;
				return 0;
			}
		}

		if (piece.getColor() == NOIR)
		{
			if (piece.getID() - 8 == ID2)
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
			if ((piece.getID() + i * 9 == ID2) || (piece.getID() - i * 9 == ID2) || (piece.getID() + i * 8 == ID2) || (piece.getID() - i * 8 == ID2) || (piece.getID() + i * 7 == ID2) || (piece.getID() - i * 7 == ID2))
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