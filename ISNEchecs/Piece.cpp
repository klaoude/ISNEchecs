#include "Piece.h"

Piece::Piece()
{

}

Piece::Piece(Type type, Couleur color, int ID)
{
	m_type = type;
	m_color = color;
	m_ID = ID;
	
	switch (type)
	{
	case Type::REINE:
		if (color == Couleur::BLANC) 
			setTexture("Sprite/White_Queen.png");
			
			
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