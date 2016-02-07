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
			y += SCREEN_HEIGHT / 8;
			x = 0;
		}

		m_board.push_back(Case(x, y, i));
		x += SCREEN_HEIGHT / 8;
	}

	GameObject* board = new GameObject("Sprites/Chess_Board.png");
	_gom->add("Board", board);
	setScale(board, 1);

	for (int i = 0; i < 8; i++) //Placement des pions
	{
		setPiece(new Piece(i+8, Type::PION, Couleur::BLANC, "WhitePawn" + std::to_string(i + 1)));
		setPiece(new Piece(i+48, Type::PION, Couleur::NOIR, "BlackPawn" + std::to_string(i + 1)));
	}

	setPiece(new Piece(0, Type::TOUR, Couleur::BLANC, "WhiteRook1")); //Placement des tours
	setPiece(new Piece(7, Type::TOUR, Couleur::BLANC, "WhiteRook2"));
	setPiece(new Piece(56, Type::TOUR, Couleur::NOIR, "BlackRook1"));
	setPiece(new Piece(63, Type::TOUR, Couleur::NOIR, "BlackRook2"));

	setPiece(new Piece(1, Type::CAVALIER, Couleur::BLANC, "WhiteKnight1")); //Placement des cavaliers
	setPiece(new Piece(6, Type::CAVALIER, Couleur::BLANC, "WhiteKnight2"));
	setPiece(new Piece(57, Type::CAVALIER, Couleur::NOIR, "BlackKnight1"));
	setPiece(new Piece(62, Type::CAVALIER, Couleur::NOIR, "BlackKnight2"));

	setPiece(new Piece(2, Type::FOU, Couleur::BLANC, "WhiteBishop1")); //Placement des fous
	setPiece(new Piece(5, Type::FOU, Couleur::BLANC, "WhiteBishop2"));
	setPiece(new Piece(58, Type::FOU, Couleur::NOIR, "BlackBishop1"));
	setPiece(new Piece(61, Type::FOU, Couleur::NOIR, "BlackBishop2"));

	setPiece(new Piece(3, Type::ROI, Couleur::BLANC, "WhiteKing")); //Placement des rois/reines
	setPiece(new Piece(4, Type::REINE, Couleur::BLANC, "WhiteQueen"));
	setPiece(new Piece(59, Type::ROI, Couleur::NOIR, "BlackKing"));
	setPiece(new Piece(60, Type::REINE, Couleur::NOIR, "BlackQueen"));

	for (size_t i = 0; i < m_board.size(); i++)
	{
		if (i < 16 || i > 47)
		{
			_gom->add(m_board.at(i).getPiece()->getTextureID(), m_board.at(i).getPiece());
			setScale(m_board.at(i).getPiece(), 2);
	}
	}

	//SET POSITION
	for (int i = 0; i < 8; i++)
	{
		_gom->get("WhitePawn" + std::to_string(i + 1))->setPosition(getCase(8 + i).getPos());
		_gom->get("BlackPawn" + std::to_string(i + 1))->setPosition(getCase(48 + i).getPos());
	}

	_gom->get("WhiteRook1")->setPosition(getCase(A1).getPos());
	_gom->get("WhiteRook2")->setPosition(getCase(A8).getPos());

	_gom->get("WhiteBishop1")->setPosition(getCase(A2).getPos());
	_gom->get("WhiteBishop2")->setPosition(getCase(A7).getPos());

	_gom->get("WhiteKnight1")->setPosition(getCase(A3).getPos());
	_gom->get("WhiteKnight2")->setPosition(getCase(A6).getPos());

	_gom->get("WhiteKing")->setPosition(getCase(A4).getPos());
	_gom->get("WhiteQueen")->setPosition(getCase(A5).getPos());

	_gom->get("BlackRook1")->setPosition(getCase(H1).getPos());
	_gom->get("BlackRook2")->setPosition(getCase(H8).getPos());

	_gom->get("BlackBishop1")->setPosition(getCase(H2).getPos());
	_gom->get("BlackBishop2")->setPosition(getCase(H7).getPos());

	_gom->get("BlackKnight1")->setPosition(getCase(H3).getPos());
	_gom->get("BlackKnight2")->setPosition(getCase(H6).getPos());

	_gom->get("BlackKing")->setPosition(getCase(H4).getPos());
	_gom->get("BlackQueen")->setPosition(getCase(H5).getPos());

	movePiece(getCase(B1).getPiece(), getCase(C1));
}

Board::~Board()
{
}


void Board::setPiece(Piece* piece)
{
	m_board.at(piece->getID()).setEmpty(0);
	m_board.at(piece->getID()).setPieceCase(piece);
}

void Board::movePiece(Piece* piece, Case caze)
{
	if (caze.isEmpty()) //Si la case est libre
	{
		if (isPossible(this, *piece, caze))
		{
			m_board.at(piece->getID()).setEmpty(true);
			m_board.at(piece->getID()).delPiece();
			piece->setID(caze.getID());
			m_board.at(caze.getID()).setEmpty(0);
			m_board.at(caze.getID()).setPieceCase(piece);
			_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py());
			std::cout << "deplacement effectuer" << std::endl;
			return;
		}
		else {
			std::cout << "deplacement impossible" << std::endl;
			return;
		}
			
	}

	if (m_board.at(caze.getID()).getPiece()->getColor() == piece->getColor())
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

Case Board::getCase(int caseID)
{
	for (size_t i = 0; i < m_board.size(); i++)
	{
		if (m_board.at(i).getID() == caseID)
			return m_board.at(i);
	}

	return m_board.at(0);
}