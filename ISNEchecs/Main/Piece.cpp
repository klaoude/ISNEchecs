#include "../Main/Piece.h"

Piece::Piece(): m_type(), m_color(), m_hasMoved(false), m_ID(0)
{
}

Piece::Piece(int ID, Type type, Couleur color, std::string textureID)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
	_textureID = textureID;
	m_hasMoved = 0;
	switch (type)
	{
	case REINE:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_Queen.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_Queen.png");
		break;
	case ROI:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_King.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_King.png");
		break;
	case PION:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_Pawn.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_Pawn.png");
		break;
	case CAVALIER:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_Knight.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_Knight.png");
		break;
	case FOU:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_Bishop.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_Bishop.png");
		break;
	case TOUR:
		if (color == BLANC)
			GameObject::setTexture("Sprites/White_Rook.png");
		if (color == NOIR)
			GameObject::setTexture("Sprites/Black_Rook.png");
		break;
	case NONEt: break;
	default: break;
	}
}

Piece::~Piece()
{
}

void Piece::draw(sf::RenderWindow& window)
{
	GameObject::draw(window);
}
