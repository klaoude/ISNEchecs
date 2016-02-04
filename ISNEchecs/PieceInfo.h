#pragma once

enum Type
{
	NONEt,
	PION,
	CAVALIER,
	TOUR,
	FOU,
	ROI,
	REINE
};

enum Couleur
{
	NONEc,
	NOIR,
	BLANC
};


inline bool isPossible(int ID, int ID2, Type type, Couleur color)
{
	if (type == CAVALIER) //CAVALIER
	{
		if ((ID + 6 == ID2) | (ID + 10 == ID2) | (ID + 15 == ID2) | (ID + 17 == ID2))
			return 1;
		else
			return 0;
	}

	if (type == TOUR) //TOUR
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{ 
			if ((ID + i * 8 == ID2) | (ID - i * 8 == ID2))
				m++;
			else
				m = m;
		}
		if (m > 1)
			return 1;
		else
			return 0;
		
	}

	if (type == FOU) //FOU
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{
			if ((ID + i * 9 == ID2) | (ID - i * 9 == ID2) | (ID + i * 7 == ID2) | (ID - i * 7 == ID2))
				m++;
			else
				m = m;
		}
		if (m > 1)
			return 1;
		else
			return 0;
	}

	if (type == ROI) //ROI
	{
		if ((ID + 1 == ID2) | (ID - 1 == ID2) | (ID + 8 == ID2) | (ID - 8 == ID2) | (ID + 9 == ID2) | (ID - 9 == ID2) | (ID + 7 == ID2) | (ID - 7 == ID2))
			return 1;
		else
			return 0;
	}

	if (type == PION) //PION
	{
		if (color == BLANC)
		{
			if (ID + 8 == ID2)
				return 1;
			else
				return 0;
		}

		if (color == NOIR)
		{
			if (ID - 8 == ID2)
				return 1;
			else
				return 0;
		}
	}

	if (type == REINE) //REINE
	{
		int m = 0;
		for (int i = 1; i < 9; i++)
		{
			if ((ID + i * 9 == ID2) | (ID - i * 9 == ID2) | (ID + i * 8 == ID2) | (ID - i * 8 == ID2) | (ID + i * 7 == ID2) | (ID - i * 7 == ID2) )
				m++;
			else
				m = m;
		}
		if (m > 0)
			return 1;
		else
			return 0;
	}
	return 0;
}