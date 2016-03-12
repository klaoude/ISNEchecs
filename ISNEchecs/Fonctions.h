#pragma once

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
					g = -i;
				else if (ceil(findroiblanc(board) / 8.0f) * 8 == floor(piece->getID() / 8.0f) * 8 + 8)
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

inline std::vector<Piece*> lb(Board *board)
{
	std::vector <Piece*> alive = board->getAliveNoir();
	std::vector<Piece*> lb; //id piece qui mangent le roi blanc
	//std::cout << "noir alive : " << alive.size() << std::endl;
	for (int i = 0; i < alive.size(); i++)
	{
		if (isPossible(board, *alive[i], board->getBoard().at(findroiblanc(board)), board->getMasterColor()))
		{
			lb.push_back(alive[i]);
		}
	}
	return lb;
}

inline std::vector<Piece*> ln(Board *board)
{
	std::vector <Piece*> alive = board->getAliveBlanc();
	std::vector<Piece*> ln; //id piece qui mangent le roi noir
	for (int i = 0; i < alive.size(); i++)
	{
		if (isPossible(board, *alive[i], board->getBoard().at(findroinoir(board)), board->getMasterColor()))
		{
			ln.push_back(alive[i]);
		}
	}
	return ln;
}

inline int echec(Board *board)
{
	int depl[8] = {-9, -8, -7, -1, +1, 7, 8, 9};
	// 0-> Rien 
	//  1-> blanc echec, king can move |  2-> blanc echec, king can't move | 3-> blanc mat
	//	4-> noir echec, king can move |  5-> noir echec, king can't move | 6-> noir mat
	int ne = 0; //noir echec
	int be = 0; //blanc echec
	int nem = 0; //blanc mat
	int bem = 0; //noir mat
	int nm = 0; //poss noir move
	int bm = 0; //poss blanc move
	std::vector<int> whbm;
	if (lb(board).size() > 0) //si un piece peut manger le roi blanc
		be++; //alors le roi blanc est en echec

	if (ln(board).size() > 0) //si un piece peut manger le roi noir
		ne++; //alors le roi noir est en echec



	for (int i=0; i < 8; i++) //check if roi blanc peut move
	{
		if (findroiblanc(board) + depl[i] < 63 && findroiblanc(board) + depl[i] > 0) //out of board
		{
			if (isPossible(board, *board->getBoard().at(findroiblanc(board)).getPiece(), board->getBoard().at(findroiblanc(board) + depl[i]), board->getMasterColor())) //si possible roi aille sur case
			{
				if (board->getBoard().at(findroiblanc(board) + depl[i]).getPiece()->getColor() == BLANC) //si il y a un allié sur cette case
				{
					bm++;
				}
				else //si pas d'allié
				{
					int aliveNoir = board->getAliveNoir().size();
					for (int j = 0; j < aliveNoir; j++)
					{						
						if (isPossible(board, *board->getAliveNoir()[j], board->getBoard().at(findroiblanc(board) + depl[i]), board->getMasterColor())) //
						{
							bm++;
							board->getBoard().at(findroiblanc(board)).setEmpty(0);
							break;
						}
					}
				}
			}				
			else //si le roi peux pas aller sur une case
				bm++; //depl bloqué en plus 
		}
		else
			bm++;
	}
	for (int i=0; i < 8; i++) //check if roi noir peut move
	{
		if (findroinoir(board) + depl[i] < 63 && findroinoir(board) + depl[i] > 0)
		{
			if (isPossible(board, *board->getBoard().at(findroinoir(board)).getPiece(), board->getBoard().at(findroinoir(board) + depl[i]), board->getMasterColor())) //si possible roi aille sur case
			{
				if (board->getBoard().at(findroinoir(board) + depl[i]).getPiece()->getColor() == NOIR)
				{
					nm++;
				}
				else
				{
					int aliveBlanc = board->getAliveBlanc().size();
					for (int j = 0; j < aliveBlanc; j++)
					{

						if (isPossible(board, *board->getAliveBlanc()[j], board->getBoard().at(findroinoir(board) + depl[i]), board->getMasterColor())) //si possible any piece aille sur case
						{
							nm++; //roi a un emplacement bloqué de plus
							break;
						}
					}
				}
			}			
			else //si le roi peux pas aller sur une case
				nm++; //depl bloqué en plus 
		}
		else
			nm++;
	}
	
	if (be > 0)
	{
		if (bm == 8) //si le roi peut pas bouger
		{
			if (lb(board).size() == 1)
			{
				int aliveBlanc = board->getAliveBlanc().size();
				for (int j = 0; j < aliveBlanc; j++)
				{
					int pathRoiSize = getPathRoi(board, lb(board)[0]).size();
					for (int i = 0; i < pathRoiSize; i++)
					{
						std::cout << "pathroi: " << getPathRoi(board, lb(board)[0])[i] << std::endl;
						if (isPossible(board, *board->getAliveBlanc()[j], board->getBoard().at(getPathRoi(board, lb(board)[0])[i]), board->getMasterColor()) && board->getAliveBlanc()[j]->getType() != ROI)
							return 2;
					}
					
				}
				std::cout << "size lb: " << lb(board).size() << std::endl;
					return 3; 

			}
			if (lb(board).size() > 1)
				return 3;
		}
		else
		{
			std::cout << "size bm: " << bm << std::endl;
			return 1;
		}
	}

	if (ne > 0)
	{
		if (nm == 8)
		{
			if (ln(board).size() == 1)
			{
				int alivePiece = board->getAlivePiece().size();
				for (int j = 0; j < alivePiece; j++)
				{
					int pathRoiSize = getPathRoi(board, ln(board)[0]).size();
					for (int i = 0; i < pathRoiSize; i++)
					{
						if (isPossible(board, *board->getBoard().at(j).getPiece(), board->getBoard().at(getPathRoi(board, ln(board)[0])[i]), board->getMasterColor()))
							return 5;
					}
					return 6;
				}
			}
			if (ln(board).size() > 1)
				return 6;
		}
		else
		{
			std::cout << "can move, size lb: " << lb(board).size() << std::endl;
			std::cout << "size bm: " << bm << std::endl;
			return 4;
		}
			
	}
	return 0;
}


