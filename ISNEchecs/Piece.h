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
	Piece(Type type, Couleur color, int ID);
	~Piece();
	Type getType() { return m_type; }
	Couleur getColor() { return m_color; }
	void setType(Type type);
	void setColor(Couleur couleur);
	//void move(Board* board, int ID);
	int getID() { return m_ID; }
	

private:
	Type m_type;
	Couleur m_color;
	//Case m_case;
	int m_ID;
};

