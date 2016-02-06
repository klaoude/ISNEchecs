#include "../Main/Board.h"
#include "../Global.h"
#include "../Fonctions.h"
#include "../Main/CaseID.h"

Board::Board()
{

}

Board::Board(GameObjectManager* gom) : _gom(gom)
{
	int x=0;
	int y=0;

	for (size_t i = 0; i < 64; i++) // on place les cases
	{
		if (i % 8 == 0 && i != 0)
		{
			std::cout << i << std::endl;
			y += SCREEN_HEIGHT / 8;
			x = 0;
		}

		m_board.push_back(Case(x, y, i+1));
		x += SCREEN_HEIGHT / 8;
	}

	GameObject* board = new GameObject("Sprites/Chess_Board.png");
	_gom->add("Board", board);

	for (int i = 0; i < 8; i++) //Placement des pions
	{
		setPiece(new Piece(i + 9, Type::PION, Couleur::BLANC, "WhitePawn" + i + 1));
		setPiece(new Piece(i + 49, Type::PION, Couleur::NOIR, "BlackPawn" + i + 1));
	}

	setPiece(new Piece(1, Type::TOUR, Couleur::BLANC, "WhiteRook1")); //Placement des tours
	setPiece(new Piece(8, Type::TOUR, Couleur::BLANC, "WhiteRook2"));
	setPiece(new Piece(57, Type::TOUR, Couleur::NOIR, "BlackRook1"));
	setPiece(new Piece(64, Type::TOUR, Couleur::NOIR, "BlackRook2"));

	setPiece(new Piece(2, Type::CAVALIER, Couleur::BLANC, "WhiteKnight1")); //Placement des cavaliers
	setPiece(new Piece(7, Type::CAVALIER, Couleur::BLANC, "WhiteKnight2"));
	setPiece(new Piece(58, Type::CAVALIER, Couleur::NOIR, "BlackKnight1"));
	setPiece(new Piece(63, Type::CAVALIER, Couleur::NOIR, "BlackKnight2"));

	setPiece(new Piece(3, Type::FOU, Couleur::BLANC, "WhiteBishop1")); //Placement des fous
	setPiece(new Piece(6, Type::FOU, Couleur::BLANC, "WhiteBishop2"));
	setPiece(new Piece(59, Type::FOU, Couleur::NOIR, "BlackBishop1"));
	setPiece(new Piece(62, Type::FOU, Couleur::NOIR, "BlackBishop2"));

	setPiece(new Piece(4, Type::ROI, Couleur::BLANC, "WhiteKing")); //Placement des rois/reines
	setPiece(new Piece(5, Type::REINE, Couleur::BLANC, "WhiteQueen"));
	setPiece(new Piece(60, Type::ROI, Couleur::NOIR, "BlackKing"));
	setPiece(new Piece(61, Type::REINE, Couleur::NOIR, "BlackQueen"));

	for (size_t i = 0; i < m_board.size(); i++)
	{
		if (i < 16 || i > 48)
			_gom->add(m_board.at(i).getPiece()->getTextureID(), m_board.at(i).getPiece());
	}
		

	/*for (size_t i = 0; i < 8; i++)
	{
		_gom->add("WhitePawn"+i+1, m_board.at(i+8).getPiece());
	}
	_gom->add("WhiteRook1", m_board.at(0).getPiece());
	_gom->add("WhiteRook2", m_board.at(7).getPiece());

	_gom->add("WhiteBishop1", m_board.at(2).getPiece());
	_gom->add("WhiteBishop2", m_board.at(5).getPiece());

	_gom->add("WhiteKnight1", m_board.at(1).getPiece());
	_gom->add("WhiteKnight2", m_board.at(6).getPiece());

	_gom->add("WhiteKing", m_board.at(4).getPiece());
	_gom->add("WhiteQueen", m_board.at(3).getPiece());
	*/

	//SET POSITION
	for (int i = 0; i < 8; i++)
	{
		_gom->get("WhitePawn" + i + 1)->setPosition(SCREEN_WIDTH / 8*i, SCREEN_WIDTH / 8);
	}

	_gom->get("WhiteRook1")->setPosition(0, 0);
	_gom->get("WhiteRook2")->setPosition(SCREEN_WIDTH / 8*7, 0);

	_gom->get("WhiteBishop1")->setPosition(SCREEN_WIDTH / 8, 0);
	_gom->get("WhiteBishop2")->setPosition(SCREEN_WIDTH / 8*6, 0);

	_gom->get("WhiteKnight1")->setPosition(SCREEN_WIDTH / 8*2, 0);
	_gom->get("WhiteKnight2")->setPosition(SCREEN_WIDTH / 8*5, 0);

	_gom->get("WhiteKing")->setPosition(SCREEN_WIDTH / 8*4, 0);
	_gom->get("WhiteQueen")->setPosition(SCREEN_WIDTH / 8*3, 0);

	movePiece(m_board.at(B1).getPiece(), m_board.at(C1));
}

Board::~Board()
{
}


void Board::setPiece(Piece* piece)
{
	m_board.at(piece->getID() - 1).setEmpty(0);
	m_board.at(piece->getID() - 1).setPieceCase(piece);
}

void Board::movePiece(Piece* piece, Case caze)
{
	if (caze.isEmpty())
	{
		if (isPossible(piece->getID(), caze.getID(), piece->getType(), piece->getColor()))
		{
			m_board.at(piece->getID()).setEmpty(1);
			m_board.at(piece->getID()).delPiece();
			piece->setID(caze.getID());
			caze.setEmpty(0);
			caze.setPieceCase(piece);
			_gom->get(m_board.at(piece->getID()).getPiece()->getTextureID())->setPosition(caze.get_px(), caze.get_py());
			std::cout << "deplacement effectuer" << std::endl;
			return;
		}
		else
			std::cout << "deplacement impossible" << std::endl;
	}

	std::cout << caze.getPiece()->getColor() << std::endl;
	std::cout << piece->getColor() << std::endl;
	if (caze.getPiece()->getColor() == piece->getColor())
	{
		std::cout << "meme color" << std::endl;
	}
	else
	{
		std::cout << "piece manger" << std::endl; //PUT OLD PIECE IN TRASH (TODO)
	} 
}

Case Board::getCase(int x, int y)
{
	int a=0; // a->x
	int b=0; // b->y
	for (size_t i = 0; i < 8; i++)
	{
		if (m_board.at(i).get_px() < x && x < m_board.at(i).get_px() + (SCREEN_WIDTH / 8))
			a = i;
	}

	for (size_t i = 0; i < 8; i++)
	{
		if (m_board.at(i*8).get_py() < y && y < m_board.at(i*8).get_py() + (SCREEN_WIDTH / 8))
			b = i;
	}
	return m_board.at(a + (b*8));

}