#include "Trashbin.h"
#include "../Graphics/GameObjectManager.h"
#include "../Main/Piece.h"

Trashbin::Trashbin()
{

}

void Trashbin::init(GameObjectManager& gom)
{
	gom.add("Trashbin", new GameObject("Sprites/trashbin.png"));
	gom.get("Trashbin")->scale(0.5f, 0.5f);
	gom.get("Trashbin")->setPosition(400, 0);
}

void Trashbin::add(Piece* piece)
{
	m_pieces.push_back(piece);
}

void Trashbin::draw(sf::RenderWindow& window)
{

}