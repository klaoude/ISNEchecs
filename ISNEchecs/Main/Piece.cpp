#include "../Main/Piece.h"

Piece::Piece()
{

}

Piece::Piece(int ID, Type type, Couleur color, std::string textureID)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
	_textureID = textureID;
	
	switch (type)
	{
	case Type::REINE:
		if (color == Couleur::BLANC) 
			setTexture("Sprites/White_Queen.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_Queen.png");
		break;
	case Type::ROI:
		if (color == Couleur::BLANC)
			setTexture("Sprites/White_King.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_King.png");
		break;
	case Type::PION:
		if (color == Couleur::BLANC)
			setTexture("Sprites/White_Pawn.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_Pawn.png");
		break;
	case Type::CAVALIER:
		if (color == Couleur::BLANC)
			setTexture("Sprites/White_Knight.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_Knight.png");
		break;
	case Type::FOU:
		if (color == Couleur::BLANC)
			setTexture("Sprites/White_Bishop.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_Bishop.png");
		break;
	case Type::TOUR:
		if (color == Couleur::BLANC)
			setTexture("Sprites/White_Rook.png");
		if (color == Couleur::NOIR)
			setTexture("Sprites/Black_Rook.png");
		break;
	}
}

Piece::~Piece()
{

}

void Piece::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}