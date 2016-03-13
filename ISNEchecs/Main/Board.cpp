#include "../Main/Board.h"
#include "../Global.h"
#include "../Fonctions.h"
#include "../IsPossible.h"
#include "../Main/CaseID.h"


std::vector<Type> pnoir;
std::vector<Type> pblanc;

Board::Board()
{
	s_pieceA = nullptr;
	s_pieceB = nullptr;
}

Board::Board(GameObjectManager* gom, Couleur mc) : _gom(gom)
{
	_hitmarker =new Son("Sound/hitmarker.wav");
	s_pieceA = nullptr;
	s_pieceB = nullptr;
	_masterColor = mc;
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

	GameObject* board = new GameObject("Sprites/board.png");
	setScale(board, 1);
	_gom->setBackground(board);

	int add = 0;
	if (_masterColor == BLANC)
		add = 63;

	for (int i = 0; i < 8; i++) //Placement des pions
	{
		setPiece(new Piece(abs(add-(i+8)), Type::PION, Couleur::BLANC, "WhitePawn" + std::to_string(i + 1)));
		setPiece(new Piece(abs(add-(i+48)), Type::PION, Couleur::NOIR, "BlackPawn" + std::to_string(i + 1)));
	}

	setPiece(new Piece(abs(add - 0), Type::TOUR, Couleur::BLANC, "WhiteRook1")); //Placement des tours
	setPiece(new Piece(abs(add - 7), Type::TOUR, Couleur::BLANC, "WhiteRook2"));
	setPiece(new Piece(abs(add - 56), Type::TOUR, Couleur::NOIR, "BlackRook1"));
	setPiece(new Piece(abs(add - 63), Type::TOUR, Couleur::NOIR, "BlackRook2"));

	setPiece(new Piece(abs(add - 1), Type::CAVALIER, Couleur::BLANC, "WhiteKnight1")); //Placement des cavaliers
	setPiece(new Piece(abs(add - 6), Type::CAVALIER, Couleur::BLANC, "WhiteKnight2"));
	setPiece(new Piece(abs(add - 57), Type::CAVALIER, Couleur::NOIR, "BlackKnight1"));
	setPiece(new Piece(abs(add - 62), Type::CAVALIER, Couleur::NOIR, "BlackKnight2"));

	setPiece(new Piece(abs(add - 2), Type::FOU, Couleur::BLANC, "WhiteBishop1")); //Placement des fous
	setPiece(new Piece(abs(add - 5), Type::FOU, Couleur::BLANC, "WhiteBishop2"));
	setPiece(new Piece(abs(add - 58), Type::FOU, Couleur::NOIR, "BlackBishop1"));
	setPiece(new Piece(abs(add - 61), Type::FOU, Couleur::NOIR, "BlackBishop2"));

	setPiece(new Piece(abs(add - 3), Type::ROI, Couleur::BLANC, "WhiteKing")); //Placement des rois/reines
	setPiece(new Piece(abs(add - 4), Type::REINE, Couleur::BLANC, "WhiteQueen"));
	setPiece(new Piece(abs(add - 59), Type::ROI, Couleur::NOIR, "BlackKing"));
	setPiece(new Piece(abs(add - 60), Type::REINE, Couleur::NOIR, "BlackQueen"));

	for (size_t i = 0; i < m_board.size(); i++)
	{
		if (i < 16 || i > 47)
		{
			_gom->add(m_board.at(i).getPiece()->getTextureID(), m_board.at(i).getPiece());
			setScale(m_board.at(i).getPiece(), 2);
			_gom->get(m_board.at(i).getPiece()->getTextureID())->setPosition(getCase(m_board.at(i).getPiece()->getID()).getPos());
			if (m_board.at(i).getPiece()->getColor() == BLANC)
				_aliveBlanc.push_back(m_board.at(i).getPiece());
			else if (m_board.at(i).getPiece()->getColor() == NOIR)
				_aliveNoir.push_back(m_board.at(i).getPiece());
			_alivePiece.push_back(m_board.at(i).getPiece());
		}
	}
	for each (Piece* piece in _aliveNoir)
	{
		std::cout << piece->getID() << std::endl;
	}
}

Board::~Board()
{
}


void Board::setPiece(Piece* piece)
{
	m_board.at(piece->getID()).setEmpty(0);
	m_board.at(piece->getID()).setPieceCase(piece);
}

bool Board::movePiece(Piece* piece, Case caze)
{

	Piece none(0, NONEt, NONEc, "");
	if (caze.isEmpty()) //Si la case est libre
	{
		if (piece->getType() == ROI) //rock
		{
			if (_masterColor == BLANC)
			{
				if (piece->getID() + 2 == caze.getID() && isPossible(this, *piece, caze, _masterColor)) //petit rock 
				{
					_gom->get(m_board.at(piece->getID() + 3).getPiece()->getTextureID())->setPosition(caze.get_px() - PIECE_SIZE, caze.get_py()); //sprite
					m_board.at(piece->getID() + 3).setEmpty(true); //setempty old
					m_board.at(piece->getID() + 3).delPiece();  //delpiece old
					m_board.at(piece->getID() + 3).getPiece()->setID(caze.getID() - 1); //new id
					m_board.at(piece->getID() + 3).getPiece()->setHasMoved(1); //hasmoved
					m_board.at(caze.getID() + 1).setEmpty(0); //setprise
					m_board.at(caze.getID() + 1).setPieceCase(m_board.at(piece->getID() + 3).getPiece()); //setpiececase

					_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite
					m_board.at(piece->getID()).setEmpty(true); //setempty old
					m_board.at(piece->getID()).delPiece();  //delpiece old
					piece->setID(caze.getID()); //new id
					piece->setHasMoved(1); //hasmoved
					m_board.at(caze.getID()).setEmpty(0); //setprise
					m_board.at(caze.getID()).setPieceCase(piece); //setpiececase

					std::cout << "grand rock effectuer" << std::endl;
				}
				if (piece->getID() - 2 == caze.getID() && isPossible(this, *piece, caze, _masterColor)) //grand rock 
				{
					_gom->get(m_board.at(piece->getID() - 4).getPiece()->getTextureID())->setPosition(caze.get_px() + PIECE_SIZE, caze.get_py()); //sprite
					m_board.at(piece->getID() - 4).setEmpty(true); //setempty old
					m_board.at(piece->getID() - 4).delPiece();  //delpiece old
					m_board.at(piece->getID() - 4).getPiece()->setID(caze.getID() - 1); //new id
					m_board.at(piece->getID() - 4).getPiece()->setHasMoved(1); //hasmoved
					m_board.at(caze.getID() - 1).setEmpty(0); //setprise
					m_board.at(caze.getID() - 1).setPieceCase(m_board.at(piece->getID() - 4).getPiece()); //setpiececase

					_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite
					m_board.at(piece->getID()).setEmpty(true); //setempty old
					m_board.at(piece->getID()).delPiece();  //delpiece old
					piece->setID(caze.getID()); //new id
					piece->setHasMoved(1); //hasmoved
					m_board.at(caze.getID()).setEmpty(0); //setprise
					m_board.at(caze.getID()).setPieceCase(piece); //setpiececase

					std::cout << "petit rock effectuer" << std::endl;
				}
			}

			if (_masterColor == NOIR)
			{
				if (piece->getID() + 2 == caze.getID() && isPossible(this, *piece, caze, _masterColor)) //grand rock 
				{
					_gom->get(m_board.at(piece->getID() + 4).getPiece()->getTextureID())->setPosition(caze.get_px() - PIECE_SIZE, caze.get_py()); //sprite
					m_board.at(piece->getID() + 4).setEmpty(true); //setempty old
					m_board.at(piece->getID() + 4).delPiece();  //delpiece old
					m_board.at(piece->getID() + 4).getPiece()->setID(caze.getID() - 1); //new id
					m_board.at(piece->getID() + 4).getPiece()->setHasMoved(1); //hasmoved
					m_board.at(caze.getID() + 1).setEmpty(0); //setprise
					m_board.at(caze.getID() + 1).setPieceCase(m_board.at(piece->getID() + 4).getPiece()); //setpiececase

					_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite
					m_board.at(piece->getID()).setEmpty(true); //setempty old
					m_board.at(piece->getID()).delPiece();  //delpiece old
					piece->setID(caze.getID()); //new id
					piece->setHasMoved(1); //hasmoved
					m_board.at(caze.getID()).setEmpty(0); //setprise
					m_board.at(caze.getID()).setPieceCase(piece); //setpiececase

					std::cout << "grand rock effectuer" << std::endl;
				}
				if (piece->getID() - 2 == caze.getID() && isPossible(this, *piece, caze, _masterColor)) //petit rock 
				{
					_gom->get(m_board.at(piece->getID() - 3).getPiece()->getTextureID())->setPosition(caze.get_px() + PIECE_SIZE, caze.get_py()); //sprite
					m_board.at(piece->getID() - 3).setEmpty(true); //setempty old
					m_board.at(piece->getID() - 3).delPiece();  //delpiece old
					m_board.at(piece->getID() - 3).getPiece()->setID(caze.getID() - 1); //new id
					m_board.at(piece->getID() - 3).getPiece()->setHasMoved(1); //hasmoved
					m_board.at(caze.getID() - 1).setEmpty(0); //setprise
					m_board.at(caze.getID() - 1).setPieceCase(m_board.at(piece->getID() - 3).getPiece()); //setpiececase

					_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite
					m_board.at(piece->getID()).setEmpty(true); //setempty old
					m_board.at(piece->getID()).delPiece();  //delpiece old
					piece->setID(caze.getID()); //new id
					piece->setHasMoved(1); //hasmoved
					m_board.at(caze.getID()).setEmpty(0); //setprise
					m_board.at(caze.getID()).setPieceCase(piece); //setpiececase

					std::cout << "petit rock effectuer" << std::endl;
				}
			}
					
		} //FIN ROCK

		if (isPossible(this, *piece, caze, _masterColor)) //deplacement
		{
			_hitmarker->play();
			Piece* oldval = piece;
			m_board.at(piece->getID()).setEmpty(true); //setempty old
			m_board.at(piece->getID()).delPiece();  //delpiece old
			piece->setID(caze.getID()); //new id
			piece->setHasMoved(1); //hasmoved
			m_board.at(caze.getID()).setEmpty(0); //setprise
			m_board.at(caze.getID()).setPieceCase(piece); //setpiececase
			_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite
			

			Piece* newVal = piece;
			std::replace(_alivePiece.begin(), _alivePiece.end(), oldval, newVal);
			std::replace(_aliveNoir.begin(), _aliveNoir.end(), oldval, newVal);
			std::replace(_aliveBlanc.begin(), _aliveBlanc.end(), oldval, newVal);
			std::cout << "deplacement effectuer" << std::endl;
			std::cout << "echec: " << echec(this) << std::endl;
			if (echec(this) > 0)
				std::cout << "echec mat: " << echecm(this) << std::endl;

			
			return true;
		}
		else {
			std::cout << "deplacement impossible" << std::endl;
			return false;
		}
			
	}

	if (m_board.at(caze.getID()).getPiece()->getColor() == piece->getColor()) //meme color
	{
		std::cout << "meme color" << std::endl;
		return false;
	}
	else if (isPossible(this, *piece, caze, _masterColor))
	{
		if (find(&_alivePiece, caze.getPiece()) != -1)
			_alivePiece.erase(_alivePiece.begin() + find(&_alivePiece, caze.getPiece()));
		if (find(&_aliveNoir, caze.getPiece()) != -1)
			_aliveNoir.erase(_aliveNoir.begin() + find(&_aliveNoir, caze.getPiece()));
		if (find(&_aliveBlanc, caze.getPiece()) != -1)
			_aliveBlanc.erase(_aliveBlanc.begin() + find(&_aliveBlanc, caze.getPiece()));

		if (piece->getColor() == BLANC) //piece noire mangée
		{
			pblanc.push_back(caze.getPiece()->getType()); //push type in corbeile
			_gom->remove(caze.getPiece()->getTextureID()); //del sprite
			caze.delPiece(); // del m_piece
			m_board.at(piece->getID()).setEmpty(true); //setempty old
			m_board.at(piece->getID()).delPiece();  //delpiece old
			piece->setID(caze.getID()); //new id
			piece->setHasMoved(1); //hasmoved
			m_board.at(caze.getID()).setEmpty(0); //setprise
			m_board.at(caze.getID()).setPieceCase(piece); //setpiececase
			_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite 
			std::cout << "piece mangee" << std::endl;
			std::cout << "echec: " << echec(this) << std::endl;
			if (echec(this) > 0)
				std::cout << "echec mat: " << echecm(this) << std::endl;
		}

		if (piece->getColor() == NOIR) //piece blanche mangée
		{
			_gom->remove(caze.getPiece()->getTextureID()); //del sprite
			pnoir.push_back(caze.getPiece()->getType()); //push type in corbeille
			caze.delPiece(); //del m_piece
			m_board.at(piece->getID()).setEmpty(true); //setempty old
			m_board.at(piece->getID()).delPiece();  //delpiece old
			piece->setID(caze.getID()); //new id
			piece->setHasMoved(1); //hasmoved
			m_board.at(caze.getID()).setEmpty(0); //setprise
			m_board.at(caze.getID()).setPieceCase(piece); //setpiececase
			_gom->get(piece->getTextureID())->setPosition(caze.get_px(), caze.get_py()); //sprite 
			std::cout << "piece mangee" << std::endl;
			std::cout << "echec: " << echec(this) << std::endl;
			if (echec(this) > 1)
				std::cout << "echec mat: " << echecm(this) << std::endl;
		}		
		
		return true;
	} 
	else 
	{
		std::cout << "deplacment impossible" << std::endl;
		return false;
	}
		
}

Case Board::getCase(int x, int y)
{
	int a=0; // a->x
	int b=0; // b->y
	for (size_t i = 0; i < 8; i++)
	{
		if (m_board.at(i).get_px() <= x && x <= m_board.at(i).get_px() + (SCREEN_WIDTH / 8))
			a = i;
	}

	for (size_t i = 0; i < 8; i++)
	{
		if (m_board.at(i*8).get_py() <= y && y <= m_board.at(i*8).get_py() + (SCREEN_WIDTH / 8))
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

void Board::simuleMove(Piece* piece, Case caze)
{
	s_oldCaseID = piece->getID();
	s_pieceA = piece;
	s_newCaseID = caze.getID();

	if (!caze.isEmpty())
		s_pieceB = caze.getPiece();
	else
		s_pieceB = nullptr;

	m_board.at(piece->getID()).setEmpty(true); //setempty old
	m_board.at(piece->getID()).delPiece();  //delpiece old
	piece->setID(caze.getID()); //new id
	m_board.at(caze.getID()).setEmpty(0); //setprise
	m_board.at(caze.getID()).setPieceCase(piece); //setpiececase	
}

void Board::undoSimileMove()
{
	m_board.at(s_newCaseID).setEmpty(true); //setempty old
	m_board.at(s_newCaseID).delPiece();  //delpiece old
	s_pieceA->setID(s_oldCaseID); //new id
	m_board.at(s_oldCaseID).setEmpty(0); //setprise
	m_board.at(s_oldCaseID).setPieceCase(s_pieceA); //setpiececase

	if (s_pieceB != nullptr)
	{
		s_pieceB->setID(s_newCaseID);
		m_board.at(s_newCaseID).setEmpty(false);
		m_board.at(s_newCaseID).setPieceCase(s_pieceB);
	}

	s_oldCaseID = 0;
	s_newCaseID = 0;
	s_pieceA = nullptr;
	s_pieceB = nullptr;
}