#include "Board.h"
#include "Case.h"

Board::Board()
{
	int x=0;
	int y=0;

	for (size_t i = 0; i < 64; i++)
	{
		if (i % 8 == 0 && i != 0)
		{
			y += 100;
			x = 0;
		}


		m_board.push_back(Case(x, y));
		x += 100;
		

	}
}


Board::~Board()
{
}

Case Board::get_case(int ID)
{
	return m_board.at(ID - 1);
}