#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Global.h"
#include "IsPossible.h"

inline std::vector<int> getPath(Board* board, Piece* piece, Couleur color)
{
	Couleur enemyColor;
	if (color == BLANC)
		enemyColor = NOIR;
	else if (color == NOIR)
		enemyColor = BLANC;

	std::vector<int> ret;
	switch (piece->getType())
	{
	case PION:
		if (piece->getID() + 8 < 64)
			if (board->getCase(piece->getID() + 8).isEmpty())
				ret.push_back(piece->getID() + 8);

		if (piece->getID() + 7 < 64)
			if (board->getCase(piece->getID() + 7).getPiece()->getColor() == enemyColor)
				ret.push_back(piece->getID() + 7);

		if (piece->getID() + 7 < 64)
			if (board->getCase(piece->getID() + 9).getPiece()->getColor() == enemyColor)
				ret.push_back(piece->getID() + 9);
		break;
	case CAVALIER:

		break;
	}
}


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

inline int find(std::vector<Piece*> vec, Piece* piece)
{
	for (auto i = 0; i < vec.size(); i++)
	{
		if (vec.at(i) == piece)
			return i;
	}
	return 0;
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
	for (int i = 0; i < 64; i++)
	{
		if (board->getBoard().at(i).getPiece()->getType() == ROI && board->getBoard().at(i).getPiece()->getColor() == NOIR)
			return i;
	}
	return 0;
}

inline int findroiblanc(Board *board)
{
	for (int i = 0; i < 64; i++)
	{
		if (board->getBoard().at(i).getPiece()->getType() == ROI && board->getBoard().at(i).getPiece()->getColor() == BLANC)
			return i;
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
			int hg; //diag haut gauche
			int hd; //diag haut droite
			int bg; //diag bas gauche
			int bd; //diag bas droite
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
				for (int i; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}

		if (piece->getType() == TOUR)
		{
			int h; //haut
			int b; //bas
			int g; //gauche
			int d; //droite
			for (int i = 1; i < 8; i++)
			{
				if (findroiblanc(board) == piece->getID() + i * 8)
					b = i;
				else if (findroiblanc(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroiblanc(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
					g = -i;
				else if (ceil(findroiblanc(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
					d = i;
			}

			if (b > 0)
			{
				for (int i; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}
		}

		if (piece->getType() == REINE)
		{
			int h; //haut
			int b; //bas
			int g; //gauche
			int d; //droite
			int hg; //diag haut gauche
			int hd; //diag haut droite
			int bg; //diag bas gauche
			int bd; //diag bas droite
			for (int i = 1; i < 8; i++)
			{
				if (findroiblanc(board) == piece->getID() + i * 8)
					b = i;
				else if (findroiblanc(board) == piece->getID() - i * 8)
					h = -i;
				else if (floor(findroiblanc(board) / 8) * 8 + 8 == ceil(piece->getID() / 8.0f) * 8)
					g = -i;
				else if (ceil(findroiblanc(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
					d = i;
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
				for (int i; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}


			if (bd > 0)
			{
				for (int i; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i; i > hd; i--)//de id a case avant le roi
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
			int hg; //diag haut gauche
			int hd; //diag haut droite
			int bg; //diag bas gauche
			int bd; //diag bas droite
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
				for (int i; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}

		if (piece->getType() == TOUR)
		{
			int h; //haut
			int b; //bas
			int g; //gauche
			int d; //droite
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
				for (int i; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}
		}

		if (piece->getType() == REINE)
		{
			int h; //haut
			int b; //bas
			int g; //gauche
			int d; //droite
			int hg; //diag haut gauche
			int hd; //diag haut droite
			int bg; //diag bas gauche
			int bd; //diag bas droite
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
				for (int i; i < b; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (h < 0)
			{
				for (int i; i > h; i--) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 8);
				}
				return path;
			}

			if (d > 0)
			{
				for (int i; i < d; i++) //de id a case avant le roi
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}

			if (g < 0)
			{
				for (int i; i > g; i--) //de id a case avant le roi 
				{
					path.push_back(piece->getID() + i);
				}
				return path;
			}


			if (bd > 0)
			{
				for (int i; i < bd; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (hg < 0)
			{
				for (int i; i > hg; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 9);
				}
				return path;
			}

			if (bg > 0)
			{
				for (int i; i < bg; i++)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}

			if (hd < 0)
			{
				for (int i; i > hd; i--)//de id a case avant le roi
				{
					path.push_back(piece->getID() + i * 7);
				}
				return path;
			}
		}
	}
	return path;

}

inline std::vector<Piece*> lb(Board *board)
{
	std::vector<Piece*> lb; //id piece qui mangent le roi blanc
	for (int i = 0; i < 64; i++)
	{
		if (isPossible(board, *board->getBoard().at(i).getPiece(), board->getBoard().at(findroiblanc(board)), board->getMasterColor()))
			lb.push_back(board->getBoard().at(i).getPiece());

	}
	return lb;
}

inline std::vector<Piece*> ln(Board *board)
{
	std::vector<Piece*> ln; //id piece qui mangent le roi noir
	for (int i = 0; i < 64; i++)
	{
		if (isPossible(board, *board->getBoard().at(i).getPiece(), board->getBoard().at(findroinoir(board)), board->getMasterColor()))
			ln.push_back(board->getBoard().at(i).getPiece());
	}
	return ln;
}

inline std::map<Piece*, std::vector<int>> echec(Board *board)
{
	int depl[8] = {-9, -8, -7, -1, +1, 7, 8, 9};
	int deplb = 0;
	int depln = 0;
	// 0-> Rien 
	// be 1-> blanc echec | ne 2-> noir echec
	// bem 3-> blanc mat | nem 4-> noir mat
	int ne=0;
	int be=0;
	int nem=0;
	int bem=0;
	int bm = 0;
	int nm = 0;
	std::map<Piece*, std::vector<int>> mapb;
	std::map<Piece*, std::vector<int>> mapn;
	
	if (be > 0)
	{
		for (int i = 0; i < lb(board).size(); i++)
		{
			mapb.emplace(std::pair <Piece*, std::vector<int>>(lb(board)[i], getPathRoi(board, lb(board)[i])));
		}

		return mapb;
	}

	if (ne > 0)
	{
		for (int i = 0; i < ln(board).size(); i++)
		{
			mapn.emplace(std::pair <Piece*, std::vector<int>>(ln(board)[i], getPathRoi(board, ln(board)[i])));
		}

		return mapn;
	}

	return mapb;
}