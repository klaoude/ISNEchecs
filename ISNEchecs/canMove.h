#pragma once

#include <iostream>
#include <chrono>

#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Main\Board.h"
#include "Fonctions.h"
#include "Global.h"

inline bool blancMove(Board board, Piece piece, Case caze, Couleur color, int echeck)
{
	std::vector<Piece*> lbr = lb(&board);
	int echecr = echeck;
	bool isPos = isPossible(&board, piece, caze, color);
	int roiBlanc = findroiblanc(&board);
	bool ennmove = 0;
	bool isOnPath = 0;

	if (echecr == 1) //si le roi blanc est en echec
	{
		if (bm(&board) < 8) //if roi can move
		{
			if (piece.getType() == ROI) //si on souhaite deplacer le roi
			{
				if (isPos) //si le roi peut aller sur la case
				{
					for (int j = 0; j < board.getAliveNoir().size(); j++)
					{
						board.simuleMove(board.getBoard().at(roiBlanc).getPiece(), caze);
						if (isPossible(&board, *board.getAliveNoir()[j], caze, board.getMasterColor())) //si une piece ennemi peut aller sur cette case
						{
							board.undoSimileMove();
							ennmove = 1;
							break;
						}
						board.undoSimileMove();
					}
					if (ennmove == 1) //si une piece peut aller sur cette case
						return 0; //le roi peut pas bouger
					else //si personne ne peux aller sur la case
						return 1; //le roi peux bouger
				}
			}
			else if (lbr.size() == 1)//si la piece n'est pas un roi et qu'il n'y a qu'une seule piece qui met le roi en echec
			{
				std::cout << "path size:" << getPathRoi(&board, lbr[0]).size() << std::endl;
				for (int i = 0; i < getPathRoi(&board, lbr[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(&board, lbr[0])[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}
			else //si pas un roi et que plusieurs pieces metteent le roi en echec
				return 0;
		}

		else //if roi can't move
		{
			if (piece.getType() == ROI) //si on veut bouger le roi
				return 0;
			else
			{
				for (int i = 0; i < getPathRoi(&board, lbr[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(&board, lbr[0])[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}
		}

	}

	else if (echecr != 1) //si le roi blanc n'est pas en echec
	{
		if (isPos) //si c'est possible d'aller sur cette case 
		{
			if (caze.getPiece()->getColor() == BLANC) //s'il y'a un alli� sur la case
				return 0;
			else //SI LE DEPL MET LE ROI EN ECHEC
			{
				board.simuleMove(&piece, caze);
				if (echec(&board) == 1) //si une piece ennemi peut aller sur le roi
				{
					ennmove = 1;
				}
				board.undoSimileMove();

				if (ennmove == 1) //si une piece peut aller sur cette case
					return 0; //le roi peut pas bouger
				else //si personne ne peux aller sur la case
					return 1; //le roi peux bouger
			}
		}
		return 0;
	}
	else
		return 0;
}

inline bool noirMove(Board board, Piece piece, Case caze, Couleur color, int echeck)
{
	std::vector<Piece*> lnr;
	int echecr = echeck;
	if (echecr > 0)
		lnr = ln(&board);
	int roiNoir = findroinoir(&board);
	bool isPos = isPossible(&board, piece, caze, color);
	bool ennmove = 0;
	bool isOnPath = 0;

	//Variable Optimisation
	std::vector<Piece*> aliveBlanc;
	if ((echecr == 4) && isPos && piece.getType() == ROI)
		aliveBlanc = board.getAliveBlanc();

	std::vector<int> pathRoi;
	if ((echecr == 4 || echecr == 5) && lnr.size() == 1 && piece.getType() != ROI)
		pathRoi = getPathRoi(&board, lnr[0]);
	//---------------------

	if (echecr == 2) //si le roi noir est en echec
	{
		if (nm(&board) < 8) //if roi can move
		{
			if (piece.getType() == ROI) //si on souhaite deplacer le roi
			{
				if (isPos) //si le roi peut aller sur la case
				{
					for (int j = 0; j < aliveBlanc.size(); j++)
					{
						board.simuleMove(board.getBoard().at(roiNoir).getPiece(), caze);
						if (isPossible(&board, *aliveBlanc[j], caze, board.getMasterColor())) //si une piece ennemi peut aller sur cette case
						{
							ennmove = 1;
							board.undoSimileMove();
							break;
						}
						board.undoSimileMove();

					}
					if (ennmove == 1) //si une piece peut aller sur cette case
						return 0; //le roi peut pas bouger
					else //si personne ne peux aller sur la case
						return 1; //le roi peux bouger
				}
			}
			else if (lnr.size() == 1)//si la piece n'est pas un roi et qu'il n'y a qu'une seule piece qui met le roi en echec
			{
				for (int i = 0; i < pathRoi.size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == pathRoi[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}
			else //si pas un roi et que plusieurs pieces metteent le roi en echec
				return 0;
		}

		else //if roi can't move
		{
			if (piece.getType() == ROI) //si on veut bouger le roi
				return 0;
			else
			{
				for (int i = 0; i < pathRoi.size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == pathRoi[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}
		}
	}

	else if (echecr < 2) //si le roi noir n'est pas en echec
	{
		if (isPos) //si c'est possible d'aller sur cette case 
		{
			if (caze.getPiece()->getColor() == NOIR) //s'il y'a un alli� sur la case
				return 0;
			else //NEED ADD SI LE DEPL MET LE ROI EN ECHEC
			{
				board.simuleMove(&piece, caze);
				if (echec(&board) == 2) //si une piece ennemi peut aller sur cette case
				{
					ennmove = 1;
				}
				board.undoSimileMove();

				if (ennmove == 1) //si une piece peut aller sur cette case
					return 0; //le roi peut pas bouger
				else //si personne ne peux aller sur la case
					return 1; //le roi peux bouger
			}
		}
		return 0;
	}
	else
		return 0;
}

inline bool canMove(Board board, Piece piece, Case caze, Couleur color, int echec)
{
	switch (piece.getColor())
	{
	case BLANC:
		return blancMove(board, piece, caze, color, echec);
		break;
	case NOIR:
		return noirMove(board, piece, caze, color, echec);
		break;
	}
}

inline std::vector<int> getAllPath(Board* board, Piece* piece, Couleur color)
{
	std::vector<int> possible;
	std::vector<int> ret;
	int _echec = echec(board);
	for (auto i = 0; i < 64; i++)
	{
		if (isPossible(board, *piece, board->getCase(i), color))
			possible.push_back(i);
	}
	for (auto i = 0; i < possible.size(); i++)
	{
		if (canMove(*board, *piece, board->getCase(possible[i]), color, _echec))
			ret.push_back(possible[i]);
	}
	return ret;
}

inline bool isPieceOnPath(Board* board, Piece* pieceA, Piece* pieceB)
{
	auto path = getAllPath(board, pieceA, pieceA->getColor());
	for (int i = 0; i < path.size(); i++)
	{
		if (board->getCase(path[i]).getPiece() == pieceB)
			return true;
	}
	return false;
}