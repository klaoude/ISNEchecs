#include <vector>

#include <SFML\Graphics.hpp>

class GameObjectManager;
class Piece;

class Trashbin
{
public:
	Trashbin();

	void init(GameObjectManager& gom);
	void add(Piece* piece);
	void draw(sf::RenderWindow& window);
private:
	std::vector<Piece*> m_pieces;
};