#pragma once
#include "Case.h"
#include <vector>



class Board
{
public:
	Board();
	~Board();
	Case get_case(int ID);

private:
	std::vector<Case> m_board;

};
