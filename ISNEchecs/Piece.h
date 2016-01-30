#pragma once
#include <iostream>

enum Type 
{
	PION,
	CAVALIER,
	TOUR,
	FOU,
	ROI,
	REINE
};

class Piece
{
public:
	Piece(Type type);
	~Piece();

private:
	Type m_type;
};

