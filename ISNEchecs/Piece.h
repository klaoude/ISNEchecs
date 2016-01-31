#pragma once
#include <iostream>

enum Type 
{
	NONE,
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

class Piece
{
public:

	Piece(Type type, Couleur color);
	~Piece();
	Type getType() { return m_type; }
	Couleur getColor() { return m_color; }
	void setType(Type type);
	void setColor(Couleur couleur);

private:
	Type m_type;
	Couleur m_color;
};

