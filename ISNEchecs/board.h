#pragma once
#include "Case.h"
#include <vector>



class Board
{
public:
	Board();
	~Board();
	Case getCase(int ID);
	void getPiece(int ID);

private:
	std::vector<Case> m_board;

};
