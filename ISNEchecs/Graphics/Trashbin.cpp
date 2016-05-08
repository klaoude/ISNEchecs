#include "Trashbin.h"
#include "../Graphics/GameObjectManager.h"
#include "../Main/Piece.h"
#include "../Global.h"

Trashbin::Trashbin()
{

}

void Trashbin::init(GameObjectManager& gom)
{
	gom.add("Trashbin", new GameObject("Sprites/trashbin.png"));
	gom.get("Trashbin")->scale(SCREEN_HEIGHT / 1000.0f, SCREEN_WIDTH / 1000.0f);
	gom.get("Trashbin")->setPosition(BOARD_SIZE, 0);
}

void Trashbin::add(Piece* piece)
{
	m_pieces.push_back(piece);
}

void Trashbin::draw(sf::RenderWindow& window)
{
	int nbPieceBlanche = 0;
	for(int i = 0; i < m_pieces.size(); i++)
	{
		m_pieces[i]->scale(1, 1);
		if(m_pieces[i]->getColor() == BLANC)
		{
			m_pieces[i]->setPosition(BOARD_SIZE, PIECE_SIZE * nbPieceBlanche);
			nbPieceBlanche++;
		}
		else
		{
			m_pieces[i]->setPosition(BOARD_SIZE + TRASHBIN_WIDTH / 2.0f, PIECE_SIZE * (i - nbPieceBlanche));
		}
	}
}