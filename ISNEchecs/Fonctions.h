#pragma once

#include <chrono>
#include <iostream>
#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Global.h"
#include "IsPossible.h"

inline int getNumPiece(std::vector<Piece*> allPiece, Type type, Couleur color)
{
	int ret = 0;
	for (int i = 0; i < allPiece.size(); i++)
	{
		if (allPiece[i]->getType() == type && allPiece[i]->getColor() == color)
			ret++;
	}
	return ret;
}

inline int find(std::vector<Piece*>* vec, Piece* piece)
{
	for (auto i = 0; i < vec->size(); i++)
	{
		if (vec->at(i) == piece)
			return i;
	}
	return -1;
}

inline int find(std::vector<int> vec, int id)
{
	for (auto i = 0; i < vec.size(); i++)
	{
		if (vec[i] == id)
			return i;
	}
	return -1;
}

inline int getValPiece(Piece* piece)
{
	switch (piece->getType())
	{
	case ROI:
		return 6;
		break;
	case REINE:
		return 5;
		break;
	case TOUR:
		return 4;
		break;
	case FOU:
		return 3;
		break;
	case CAVALIER:
		return 2;
		break;
	case PION:
		return 1;
		break;
	default:
		break;
	}
}

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

inline int findroinoir(Board *board)
{
	for (int i = 0; i < board->getAliveNoir().size(); i++)
	{
		if (board->getAliveNoir()[i]->getType() == ROI)
			return board->getAliveNoir()[i]->getID();
	}
	return 0;
}

inline int findroiblanc(Board *board)
{
	for (int i = 0; i < board->getAliveBlanc().size(); i++)
	{
		if (board->getAliveBlanc()[i]->getType() == ROI)
			return board->getAliveBlanc()[i]->getID();
	}
	return 0;
}

inline std::vector<int> getPathRoi(Board* board, Piece* piece)
{
	std::vector<int> path;
	if (piece->getColor() == BLANC)
	{
		if (piece->getType() == CAVALIER || piece->getType() == PION)
		{
			path.push_back(piece->getID());
			return path;
		}

		if (piece->getType() == FOU)
		{
			int hg=0; //diag haut gauche
			int hd=0; //diag haut droite
			int bg = 0; //diag bas gauche
			int bd=0; //diag bas droite
			for (int i = 1; i < 8; i++)
			{
				if (findroinoir(board) == piece->getID() + i * 9)
					bd = i;
				else if (findroinoir(board) == piece->getID() - i * 9)
					hg = -i;
				else if (findroinoir(board) == piece->getID() + i * 7)
					bg = i;
				else if (findroinoir(board) == piece->getID() - i * 7)
					hd = -i;
			}

			if (bd > 0)
			{
				for (int i=0; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i=0; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i=0; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i=0; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}

		if (piece->getType() == TOUR)
		{
			int h=0; //haut
			int b=0; //bas
			int g=0; //gauche
			int d=0; //droite
			for (int i = 1; i < 8; i++)
			{
				if (findroinoir(board) == piece->getID() + i * 8)
					b = i;
				else if (findroinoir(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroinoir(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
					g = -i;
				else if (ceil(findroinoir(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
					d = i;
			}

			if (b > 0)
			{
				for (int i=0; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i=0; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i=0; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i=0; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}
		}

		if (piece->getType() == REINE)
		{
			int h=0; //haut
			int b=0; //bas
			int g=0; //gauche
			int d=0; //droite
			int hg=0; //diag haut gauche
			int hd=0; //diag haut droite
			int bg=0; //diag bas gauche
			int bd=0; //diag bas droite
			for (int i = 1; i < 8; i++)
			{
				if (findroinoir(board) == piece->getID() + i * 8)
					b = i;
				else if (findroinoir(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroinoir(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
					g = -i;
				else if (ceil(findroinoir(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
					d = i;
				else if (findroinoir(board) == piece->getID() + i * 9)
					bd = i;
				else if (findroinoir(board) == piece->getID() - i * 9)
					hg = -i;
				else if (findroinoir(board) == piece->getID() + i * 7)
					bg = i;
				else if (findroinoir(board) == piece->getID() - i * 7)
					hd = -i;
			}

			if (b > 0)
			{
				for (int i=0; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i=0; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i=0; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i=0; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}


			if (bd > 0)
			{
				for (int i=0; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i=0; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i=0; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i=0; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}
	}

	if (piece->getColor() == NOIR) //noir
	{
		if (piece->getType() == CAVALIER || piece->getType() == PION)
		{
			path.push_back(piece->getID());
			return path;
		}

		if (piece->getType() == FOU)
		{
			int hg=0; //diag haut gauche
			int hd=0; //diag haut droite
			int bg=0; //diag bas gauche
			int bd = 0; //diag bas droite
			for (int i = 1; i < 8; i++)
			{
				if (findroiblanc(board) == piece->getID() + i * 9)
					bd = i;
				else if (findroiblanc(board) == piece->getID() - i * 9)
					hg = -i;
				else if (findroiblanc(board) == piece->getID() + i * 7)
					bg = i;
				else if (findroiblanc(board) == piece->getID() - i * 7)
					hd = -i;
			}

			if (bd > 0)
			{
				for (int i=0; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i=0; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i=0; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i=0; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}

		if (piece->getType() == TOUR)
		{
			int h=0 ; //haut
			int b=0; //bas
			int g=0; //gauche
			int d=0; //droite
			for (int i = 1; i < 8; i++)
			{
				if (findroiblanc(board) == piece->getID() + i * 8)
					b = i;
				else if (findroiblanc(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroiblanc(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
					for (int j = 0; j < 8; j++)
						if (findroiblanc(board) == piece->getID() - i)
							g = -i;
				else if (ceil(findroiblanc(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
					for (int j = 0; j < 8; j++)
						if (findroiblanc(board) == piece->getID() - i)
							d = i;
			}

			if (b > 0)
			{
				for (int i=0; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i=0; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i=0; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i=0; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}
		}

		if (piece->getType() == REINE)
		{
			int h = 0; //haut
			int b = 0; //bas
			int g=0; //gauche
			int d=0; //droite
			int hg=0; //diag haut gauche
			int hd=0; //diag haut droite
			int bg=0; //diag bas gauche
			int bd=0; //diag bas droite
			for (int i = 1; i < 8; i++)
			{
				if (findroiblanc(board) == piece->getID() + i * 8)
					b = i;
				else if (findroiblanc(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroiblanc(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
				{
				for (int j = 0; j < 8; j++)
				{
					if (findroiblanc(board) == piece->getID() - i)
						g = -i;
					else
						;
				}
				}
					
					
					
				else if (ceil(findroiblanc(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
				{
					for (int j = 0; j < 8; j++)
					{
						if (findroiblanc(board) == piece->getID() - i)
							d = i;
						else
							;
					}
				}
					
				else if (findroiblanc(board) == piece->getID() + i * 9)
					bd = i;
				else if (findroiblanc(board) == piece->getID() - i * 9)
					hg = -i;
				else if (findroiblanc(board) == piece->getID() + i * 7)
					bg = i;
				else if (findroiblanc(board) == piece->getID() - i * 7)
					hd = -i;
			}

			if (b > 0)
			{
				for (int i=0; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i=0; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i=0; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i=0; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}


			if (bd > 0)
			{
				for (int i=0; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i=0; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i=0; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i=0; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}
	}
	return path;

}

inline std::vector<Piece*> lb(Board *board, Couleur mastercolor)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	std::vector<Piece*> lb; //id piece qui mangent le roi blanc
	int roi = findroiblanc(board);
	bool dhd = 1;
	bool dhg = 1;
	bool dbg = 1;
	bool dbd = 1;

	//cavalier positif
	if (roi + 17 < 64) //si les deplacements positifs sont possibles
	{
		if (board->getBoard().at(roi + 17).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 17).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 17).getPiece());
		if (board->getBoard().at(roi + 15).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 15).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 15).getPiece());
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 15 < 64) //si les deplacement positifs jusqu'a +15 sont possibles
	{
		if (board->getBoard().at(roi + 15).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 15).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 15).getPiece());
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 10 < 64) //si les deplacement positifs jusqu'a +9 sont possibles
	{
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 6 < 64) //si seul +6 est possible
	{
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi + 6).getPiece());
	}

	//cavalier negatif
	if (roi - 17 > 0) //si les deplacements positifs sont possibles
	{
		if (board->getBoard().at(roi - 17).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 17).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 17).getPiece());
		if (board->getBoard().at(roi - 15).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 15).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 15).getPiece());
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 15 > 0) //si les deplacement positifs jusqu'a -15 sont possibles
	{
		if (board->getBoard().at(roi - 15).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 15).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 15).getPiece());
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 10 > 0) //si les deplacement positifs jusqu'a -9 sont possibles
	{
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 6 > 0) //si seul -6 est possible
	{
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			lb.push_back(board->getBoard().at(roi - 6).getPiece());
	}




	if (mastercolor == NOIR) //pion w/ mastercolor noir
	{
		if (board->getBoard().at(roi + 9).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 9).getPiece()->getType() == PION)
			lb.push_back(board->getBoard().at(roi + 9).getPiece());
		if (board->getBoard().at(roi + 7).getPiece()->getColor() == NOIR && board->getBoard().at(roi + 7).getPiece()->getType() == PION)
			lb.push_back(board->getBoard().at(roi + 7).getPiece());
	}
	if (mastercolor == BLANC) //pion w/ mastercolor blanc
	{
		if (board->getBoard().at(roi - 9).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 9).getPiece()->getType() == PION)
			lb.push_back(board->getBoard().at(roi - 9).getPiece());
		if (board->getBoard().at(roi - 7).getPiece()->getColor() == NOIR && board->getBoard().at(roi - 7).getPiece()->getType() == PION)
			lb.push_back(board->getBoard().at(roi - 7).getPiece());
	}

	for (int i = 1; i <= roi - (div(roi, 8).quot * 8); i++) //depl gauche
	{
		if (board->getBoard().at(roi - i).getPiece()->getColor() == NOIR && (board->getBoard().at(roi - i).getPiece()->getType() == TOUR || board->getBoard().at(roi - i).getPiece()->getType() == REINE))
			lb.push_back(board->getBoard().at(roi - i).getPiece());
		else if (!board->getBoard().at(roi - i).isEmpty())
			break;
	}

	for (int i = 1; i <= ((div(roi, 8).quot + 1) * 8) - roi; i++) //depl droite
	{
		if (board->getBoard().at(roi + i).getPiece()->getColor() == NOIR && (board->getBoard().at(roi + i).getPiece()->getType() == TOUR || board->getBoard().at(roi + i).getPiece()->getType() == REINE))
			lb.push_back(board->getBoard().at(roi + i).getPiece());
		else if (!board->getBoard().at(roi + i).isEmpty())
			break;
	}

	for (int i = 1; i < 8; i++) //depl vertical
	{
		if (roi + i * 8 < 63)
		{
			if (board->getBoard().at(roi + i * 8).getPiece()->getColor() == NOIR && (board->getBoard().at(roi + i * 8).getPiece()->getType() == TOUR || board->getBoard().at(roi + i * 8).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi + i * 8).getPiece());
			else if (!board->getBoard().at(roi + i * 8).isEmpty())
				break;
		}
		if (roi - i * 8 > 0)
		{
			if (board->getBoard().at(roi - i * 8).getPiece()->getColor() == NOIR && (board->getBoard().at(roi - i * 8).getPiece()->getType() == TOUR || board->getBoard().at(roi - i * 8).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi - i * 8).getPiece());
			else if (!board->getBoard().at(roi - i * 8).isEmpty())
				break;
		}
	}

	for (int i = 1; i < 8 - roi; i++) //depl diag bas
	{

		if (roi + i * 9 < 64 && dbd == 1)
		{
			if (board->getBoard().at(roi + i * 9).getPiece()->getColor() == NOIR && (board->getBoard().at(roi + i * 9).getPiece()->getType() == FOU || board->getBoard().at(roi + i * 9).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi + i * 9).getPiece());
			else if (!board->getBoard().at(roi + i * 9).isEmpty())
				dbd = 0;
		}
		if (roi + i * 7 < 64 && dbg == 1)
		{
			if (board->getBoard().at(roi + i * 7).getPiece()->getColor() == NOIR && (board->getBoard().at(roi + i * 7).getPiece()->getType() == FOU || board->getBoard().at(roi + i * 7).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi + i * 7).getPiece());
			else if (!board->getBoard().at(roi + i * 7).isEmpty())
				dbg = 0;
		}
		if (roi + i * 7 > 63)
			if (roi + i * 9 > 63)
				break;
	}

	for (int i = 1; i < 8; i++) //depl diag haut
	{

		if (roi - i * 9 > 0 && dhd == 1)
		{
			if (board->getBoard().at(roi - i * 9).getPiece()->getColor() == NOIR && (board->getBoard().at(roi - i * 9).getPiece()->getType() == FOU || board->getBoard().at(roi - i * 9).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi - i * 9).getPiece());
			else if (!board->getBoard().at(roi - i * 9).isEmpty())
				dhd = 0;
		}
		if (roi - i * 7 > 0 && dhg == 1)
		{
			if (board->getBoard().at(roi - i * 7).getPiece()->getColor() == NOIR && (board->getBoard().at(roi - i * 7).getPiece()->getType() == FOU || board->getBoard().at(roi - i * 7).getPiece()->getType() == REINE))
				lb.push_back(board->getBoard().at(roi - i * 7).getPiece());
			else if (!board->getBoard().at(roi - i * 7).isEmpty())
				dhg = 0;
		}

		if (roi - i * 9 < 0)
			if (roi - i * 7 < 0)
				break;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "lbtime = " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;
	return lb;
}

inline std::vector<Piece*> ln(Board *board, Couleur mastercolor)
{
	auto t1 = std::chrono::high_resolution_clock::now();
	std::vector<Piece*> ln; //id piece qui mangent le roi noir
	int roi = findroinoir(board);
	bool dhd = 1;
	bool dhg = 1;
	bool dbg = 1;
	bool dbd = 1;


	//cavalier positif
	if (roi + 17 < 64) //si les deplacements positifs sont possibles
	{		

		if (board->getBoard().at(roi + 17).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 17).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 17).getPiece());
		if (board->getBoard().at(roi + 15).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 15).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 15).getPiece());
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 15 < 64) //si les deplacement positifs jusqu'a +15 sont possibles
	{
		if (board->getBoard().at(roi + 15).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 15).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 15).getPiece());
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 10 < 64) //si les deplacement positifs jusqu'a +9 sont possibles
	{
		if (board->getBoard().at(roi + 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 10).getPiece());
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 6).getPiece());
	}
	else if (roi + 6 < 64) //si seul +6 est possible
	{
		if (board->getBoard().at(roi + 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi + 6).getPiece());
	}

	//cavalier negatif
	if (roi - 17 > 0) //si les deplacements positifs sont possibles
	{
		if (board->getBoard().at(roi - 17).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 17).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 17).getPiece());
		if (board->getBoard().at(roi - 15).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 15).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 15).getPiece());
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 15 > 0) //si les deplacement positifs jusqu'a -15 sont possibles
	{
		if (board->getBoard().at(roi - 15).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 15).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 15).getPiece());
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 10 > 0) //si les deplacement positifs jusqu'a -9 sont possibles
	{
		if (board->getBoard().at(roi - 10).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 10).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 10).getPiece());
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 6).getPiece());
	}
	else if (roi - 6 > 0) //si seul -6 est possible
	{
		if (board->getBoard().at(roi - 6).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 6).getPiece()->getType() == CAVALIER)
			ln.push_back(board->getBoard().at(roi - 6).getPiece());
	}




	if (mastercolor == BLANC) //pion w/ mastercolor BLANC
	{
		if (board->getBoard().at(roi + 9).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 9).getPiece()->getType() == PION)
			ln.push_back(board->getBoard().at(roi + 9).getPiece());
		if (board->getBoard().at(roi + 7).getPiece()->getColor() == BLANC && board->getBoard().at(roi + 7).getPiece()->getType() == PION)
			ln.push_back(board->getBoard().at(roi + 7).getPiece());
	}
	else if (mastercolor == NOIR) //pion w/ mastercolor BLANC
	{
		if (board->getBoard().at(roi - 9).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 9).getPiece()->getType() == PION)
			ln.push_back(board->getBoard().at(roi - 9).getPiece());
		if (board->getBoard().at(roi - 7).getPiece()->getColor() == BLANC && board->getBoard().at(roi - 7).getPiece()->getType() == PION)
			ln.push_back(board->getBoard().at(roi - 7).getPiece());
	}

	for (int i = 1; i <= roi - (div(roi, 8).quot * 8); i++) //depl gauche
	{
		if (roi - i < 0)
			break;
		if (board->getBoard().at(roi - i).getPiece()->getColor() == BLANC && (board->getBoard().at(roi - i).getPiece()->getType() == TOUR || board->getBoard().at(roi - i).getPiece()->getType() == REINE))
			ln.push_back(board->getBoard().at(roi - i).getPiece());
		else if (!board->getBoard().at(roi - i).isEmpty())
			break;
	}

	for (int i = 1; i < ((div(roi, 8).quot + 1) * 8) - roi; i++) //depl droite
	{
		if (roi + i > 64)
			break;
		if (board->getBoard().at(roi + i).getPiece()->getColor() == BLANC && (board->getBoard().at(roi + i).getPiece()->getType() == TOUR || board->getBoard().at(roi + i).getPiece()->getType() == REINE))
			ln.push_back(board->getBoard().at(roi + i).getPiece());
		else if (!board->getBoard().at(roi + i).isEmpty())
			break;
	}

	for (int i = 1; i < 8; i++) //depl vertical
	{
		if (roi + i * 8 < 64)
		{
			if (board->getBoard().at(roi + i * 8).getPiece()->getColor() == BLANC && (board->getBoard().at(roi + i * 8).getPiece()->getType() == TOUR || board->getBoard().at(roi + i * 8).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi + i * 8).getPiece());
			else if (!board->getBoard().at(roi + i * 8).isEmpty())
				break;
		}
		if (roi - i * 8 > 0)
		{
			if (board->getBoard().at(roi - i * 8).getPiece()->getColor() == BLANC && (board->getBoard().at(roi - i * 8).getPiece()->getType() == TOUR || board->getBoard().at(roi - i * 8).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi - i * 8).getPiece());
			else if (!board->getBoard().at(roi - i * 8).isEmpty())
				break;
		}
	}

	for (int i = 1; i < 8 - roi; i++) //depl diag bas
	{
		if (roi + i * 9 < 64 && dbd == 1)
		{
			if (board->getBoard().at(roi + i * 9).getPiece()->getColor() == BLANC && (board->getBoard().at(roi + i * 9).getPiece()->getType() == FOU || board->getBoard().at(roi + i * 9).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi + i * 9).getPiece());
			else if (!board->getBoard().at(roi + i * 9).isEmpty())
				dbd = 0;
		}
		if (roi + i * 7 < 64 && dbg == 1)
		{
			if (board->getBoard().at(roi + i * 7).getPiece()->getColor() == BLANC && (board->getBoard().at(roi + i * 7).getPiece()->getType() == FOU || board->getBoard().at(roi + i * 7).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi + i * 7).getPiece());
			else if (!board->getBoard().at(roi + i * 7).isEmpty())
				dbg = 0;
		}
		if (roi + i * 7 > 63)
			if (roi + i * 9 > 63)
				break;
	}

	for (int i = 1; i < 8; i++) //depl diag haut
	{
		if (roi - i * 9 > 0 && dhd == 1)
		{
			if (board->getBoard().at(roi - i * 9).getPiece()->getColor() == BLANC && (board->getBoard().at(roi - i * 9).getPiece()->getType() == FOU || board->getBoard().at(roi - i * 9).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi - i * 9).getPiece());
			else if (!board->getBoard().at(roi - i * 9).isEmpty())
				dhd = 0;
		}
		if (roi - i * 7 > 0 && dhg == 1)
		{
			if (board->getBoard().at(roi - i * 7).getPiece()->getColor() == BLANC && (board->getBoard().at(roi - i * 7).getPiece()->getType() == FOU || board->getBoard().at(roi - i * 7).getPiece()->getType() == REINE))
				ln.push_back(board->getBoard().at(roi - i * 7).getPiece());
			else if (!board->getBoard().at(roi - i * 7).isEmpty())
				dhg = 0;
		}

		if (roi - i * 9 < 0)
			if (roi - i * 7 < 0)
				break;
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	std::cout << "lntime = " << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << std::endl;
	return ln;
}

inline int bm(Board *board)
{
	int depl[8] = { -9, -8, -7, -1, +1, 7, 8, 9 };
	int roiBlanc = findroiblanc(board);
	auto aliveNoir = board->getAliveNoir();
	int bm = 0;
	for (int i = 0; i < 8; i++) //check if roi blanc peut move
	{
		if (roiBlanc + depl[i] < 63 && roiBlanc + depl[i] > 0) //out of board
		{
			if (isPossible(board, *board->getBoard().at(roiBlanc).getPiece(), board->getBoard().at(roiBlanc + depl[i]), board->getMasterColor())) //si possible roi aille sur case
			{
				if (board->getBoard().at(roiBlanc + depl[i]).getPiece()->getColor() == BLANC) //si il y a un allié sur cette case
				{
					bm++;
				}
				else //si pas d'allié
				{
					for (int j = 0; j < aliveNoir.size(); j++)
					{
						board->simuleMove(board->getBoard().at(roiBlanc).getPiece(), board->getBoard().at(roiBlanc + depl[i]));
						if (isPossible(board, *aliveNoir[j], board->getBoard().at(roiBlanc + depl[i]), board->getMasterColor())) //
						{

							bm++;
							board->undoSimileMove();
							break;
						}
						board->undoSimileMove();

					}
				}
			}				
			else //si le roi peux pas aller sur une case
				bm++; //depl bloqué en plus 
		}
		else
			bm++;
	}
	return bm;
}


inline int nm(Board *board)
{
	int depl[8] = { -9, -8, -7, -1, +1, 7, 8, 9 };
	int roiNoir = findroinoir(board);
	auto aliveBlanc = board->getAliveBlanc();
	int nm = 0;

	for (int i = 0; i < 8; i++) //check if roi noir peut move
	{
		if (roiNoir + depl[i] < 63 && roiNoir + depl[i] > 0)
		{
			if (isPossible(board, *board->getBoard().at(roiNoir).getPiece(), board->getBoard().at(roiNoir + depl[i]), board->getMasterColor())) //si possible roi aille sur case
			{
				if (board->getBoard().at(roiNoir + depl[i]).getPiece()->getColor() == NOIR)
				{
					nm++;
				}
				else
				{
					for (int j = 0; j < aliveBlanc.size(); j++)
					{
						board->simuleMove(board->getBoard().at(roiNoir).getPiece(), board->getBoard().at(roiNoir + depl[i]));
						if (isPossible(board, *aliveBlanc[j], board->getBoard().at(roiNoir + depl[i]), board->getMasterColor())) //si possible any piece aille sur case
						{
							board->undoSimileMove();
							nm++; //roi a un emplacement bloqué de plus
							break;
						}
						board->undoSimileMove();
					}
				}
			}			
			else //si le roi peux pas aller sur une case
				nm++; //depl bloqué en plus 
		}
		else
			nm++;
	}
	return nm;
}

inline int echec(Board* board)
{
	
	if (lb(board, board->getMasterColor()).size() > 0)
		return 1;
	if (ln(board, board->getMasterColor()).size() > 0)
		return 2;
	return 0;
}
	
inline int echecm(Board *board)
{
	int depl[8] = {-9, -8, -7, -1, +1, 7, 8, 9};
	// 0-> Rien 
	//  1-> blanc echec, king can move |  2-> blanc echec, king can't move | 3-> blanc mat
	//	4-> noir echec, king can move |  5-> noir echec, king can't move | 6-> noir mat
	int ne = 0; //noir echec
	int be = 0; //blanc echec
	int nem = 0; //blanc mat
	int bem = 0; //noir mat
	int _nm = nm(board); //poss noir move
	int _bm = bm(board); //poss blanc move
	std::vector<int> whbm;

	//Var optimisation
	int roiBlanc = findroiblanc(board);
	int roiNoir = findroinoir(board);
	auto aliveNoir = board->getAliveNoir();
	auto aliveBlanc = board->getAliveBlanc();
	Couleur mastercolor = board->getMasterColor();
	auto _lb = lb(board, mastercolor);
	auto _ln = ln(board, mastercolor);
	std::vector<int> pathRoiBlanc;
	std::vector<int> pathRoiNoir;
	if (_lb.size() > 0)
		pathRoiBlanc = getPathRoi(board, _lb[0]);
	if (_ln.size() > 0)
		pathRoiNoir = getPathRoi(board, _ln[0]);
	//----------------

	if (_lb.size() > 0) //si un piece peut manger le roi blanc
		be++; //alors le roi blanc est en echec

	if (_ln.size() > 0) //si un piece peut manger le roi noir
		ne++; //alors le roi noir est en echec	




	if (echec(board) == 1) //si roi blanc est en echec
	{
		if (_bm == 8) //if roi can't move
		{
			if (_lb.size() > 1) //si plus d'une piece mette le roi blanc en echec
			{
				return 1;
			}
			else //if qu'une piece le met en echec
			{
				for (int j = 0; j < aliveBlanc.size(); j++)
				{	
					for (int i = 0; i < pathRoiBlanc.size(); i++)
					{
						if (isPossible(board, *aliveBlanc[j], board->getBoard().at(pathRoiBlanc[i]), board->getMasterColor()) && aliveBlanc[j]->getType() != ROI)
							return 0;
					}
				}
				
				return 1;
			}
		}
		else //if roi can move
		{
			return 0;
		}
		return 0;
	}

	if (echec(board) == 2) //si roi noir est en echec
	{
		if (_nm == 8) //if roi can't move
	{
			if (_ln.size() > 1) //si plus d'une piece mette le roi blanc en echec
		{
				return 2;
			}
			else //if qu'une piece le met en echec
			{				
				for (int j = 0; j < aliveNoir.size(); j++)
				{
					for (int i = 0; i < pathRoiNoir.size(); i++)
					{
						if (isPossible(board, *aliveNoir[j], board->getBoard().at(pathRoiNoir[i]), board->getMasterColor()) && aliveNoir[j]->getType() != ROI)
							return 0;
					}
				}
				return 2;
			}
		}
		else //if roi can move
		{
			return 0;
		}
		return 0;
	}
	return 0;


	
}

inline Type strToType(std::string type)
{
	Type typef = NONEt;
	if (type == "pion")
		typef = PION;
	else if (type == "cavalier")
		typef = CAVALIER;
	else if (type == "tour")
		typef = TOUR;
	else if (type == "reine")
		typef = REINE;
	else if (type == "fou")
		typef = FOU;
	else if (type == "roi")
		typef = ROI;

	return typef;
}