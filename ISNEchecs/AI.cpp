#include "AI.h"

#include "Fonctions.h"

AI::AI(Board* board)
{
	_board = board;
}

AI::~AI()
{
}

void AI::play()
{
	int num = 0;
	if (!echec(_board))
	{
		for (int i = 0; i < 5; i++)
		{
			int numPiece = getNumPiece(_board->getAlivePiece(), _rangPiece[i], _iaColor);
			if (numPiece == 0)
				break;
			else
			{
				if (i == 1 || i == 2 || i == 3)
				{
					if (numPiece >= 2)
						num = rand() % numPiece + 1;
					else
						num = 1;
				}				
			}
		}
	}
	else
	{

	}
}