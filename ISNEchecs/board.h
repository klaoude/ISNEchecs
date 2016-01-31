#pragma once

#include <vector>

#include "Case.h"

class Board
{
public:
	Board();
	~Board();
	Case getCase(int ID);
	void getTyCo(int ID);
	std::vector<Case> getBoard() { return m_board; }

private:
	std::vector<Case> m_board;

};