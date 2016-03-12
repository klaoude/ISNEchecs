#pragma once

#include <iostream>
#include <SFML\Graphics.hpp>

#include "Main/PieceInfo.h"
#include "Main\Board.h"
#include "Fonctions.h"
#include "Global.h"

bool blancMove(Board *board, Piece piece, Case caze, Couleur color)
{
	bool ennmove = 0;
	bool isOnPath = 0;
	if (piece.getColor() == BLANC) //si on veut bouger une piece blanc
	{
		if (echec(board) == 1) //si le roi blanc est en echec et peux bouger
		{
			if (piece.getType() == ROI) //si on souhaite deplacer le roi
			{
				if (isPossible(board, piece, caze, color)) //si le roi peut aller sur la case
				{
					for (int j = 0; j < board->getAliveNoir().size(); j++)
					{

						if (isPossible(board, *board->getAliveNoir()[j], caze, board->getMasterColor())) //si une piece ennemi peut aller sur cette case
							ennmove = 1;

					}
					if (ennmove = 1) //si une piece peut aller sur cette case
						return 0; //le roi peut pas bouger
					else //si personne ne peux aller sur la case
						return 1; //le roi peux bouger
				}
			}
			else if (lb(board).size() == 1)//si la piece n'est pas un roi et qu'il n'y a qu'une seule piece qui met le roi en echec
			{
				for (int i = 0; i < getPathRoi(board, lb(board)[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(board, lb(board)[0])[i])
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
		else if (echec(board) == 2) //si le roi blanc est en echec et ne peux pas bouger
		{
			if (piece.getType() == ROI) //si on veut bouger le roi
				return 0;
			else
			{
				for (int i = 0; i < getPathRoi(board, lb(board)[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(board, lb(board)[0])[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}

		}

		else if (echec(board) < 1 || echec(board) > 3) //si le roi blanc n'est pas en echec
		{
			if (isPossible(board, piece, caze, color)) //si c'est possible d'aller sur cette case 
			{
				if (caze.getPiece()->getColor() == BLANC) //s'il y'a un allié sur la case
					return 0;
				else //NEED ADD SI LE DEPL MET LE ROI EN ECHEC
				{
					return 1;
				}
			}
		}
	}
}

bool noirMove(Board *board, Piece piece, Case caze, Couleur color)
{
	bool ennmove = 0;
	bool isOnPath = 0;
	if (piece.getColor() == NOIR) //si on veut bouger une piece noir
	{
		if (echec(board) == 4) //si le roi noir est en echec et peux bouger
		{
			if (piece.getType() == ROI) //si on souhaite deplacer le roi
			{
				if (isPossible(board, piece, caze, color)) //si le roi peut aller sur la case
				{
					for (int j = 0; j < board->getAliveBlanc().size(); j++)
					{

						if (isPossible(board, *board->getAliveBlanc()[j], caze, board->getMasterColor())) //si une piece ennemi peut aller sur cette case
							ennmove = 1;

					}
					if (ennmove = 1) //si une piece peut aller sur cette case
						return 0; //le roi peut pas bouger
					else //si personne ne peux aller sur la case
						return 1; //le roi peux bouger
				}
			}
			else if (ln(board).size() == 1)//si la piece n'est pas un roi et qu'il n'y a qu'une seule piece qui met le roi en echec
			{
				for (int i = 0; i < getPathRoi(board, ln(board)[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(board, ln(board)[0])[i])
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
		else if (echec(board) == 5) //si le roi noir est en echec et ne peux pas bouger
		{
			if (piece.getType() == ROI) //si on veut bouger le roi
				return 0;
			else
			{
				for (int i = 0; i < getPathRoi(board, ln(board)[0]).size(); i++) //si caze est sur le path de la piece qui met en echec
				{
					if (caze.getID() == getPathRoi(board, ln(board)[0])[i])
						isOnPath = 1;
				}
				if (isOnPath == 1)
					return 1;
				else
					return 0;
			}

		}

		else if (echec(board) < 4) //si le roi noir n'est pas en echec
		{
			if (isPossible(board, piece, caze, color)) //si c'est possible d'aller sur cette case 
			{
				if (caze.getPiece()->getColor() == NOIR) //s'il y'a un allié sur la case
					return 0;
				else //NEED ADD SI LE DEPL MET LE ROI EN ECHEC
				{
					return 1;
				}
			}
		}
	}
}

inline bool canMove(Board *board, Piece piece, Case caze, Couleur color)
{
	switch (piece.getColor())
	{
	case BLANC:
		return blancMove(board, piece, caze, color);
		break;
	case NOIR:
		return noirMove(board, piece, caze, color);
		break;

	}
}

inline std::vector<int> getAllPath(Board* board, Piece* piece, Couleur color)
{
	std::vector<int> ret;
	for (auto i = 0; i < 64; i++)
	{
		if (canMove(board, *piece, board->getCase(i), color))
			ret.push_back(i);
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