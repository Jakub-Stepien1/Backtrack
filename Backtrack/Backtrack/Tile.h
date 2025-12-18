#pragma once
#include <SFML/Graphics.hpp>

struct SurroundingTiles
{
	int left = 0;
	int right = 0;
	int top = 0;
	int bottom = 0;

	int topLeft = 0;
	int topRight = 0;
	int bottomLeft = 0;
	int bottomRight = 0;
};

class Tile
{
public:
	Tile();
	~Tile();

	void render(sf::RenderWindow &window);

	void setTile(int t_tile, SurroundingTiles t_surrounding);
	void setPosition(sf::Vector2f t_position);
	void setTexture(const sf::Texture& t_texture);
	void setTextureRect(SurroundingTiles t_surrounding, int t_tileType);

private:

	const sf::Vector2i TILE_SIZE{ 18, 18 };

	sf::Texture texture;

	sf::IntRect tileRect;
	sf::Sprite sprite{ texture };

	sf::RectangleShape rectangle;

	// Tile texture rectangles
	sf::IntRect grassTopLeft{ sf::Vector2i(0, 54), TILE_SIZE };
	sf::IntRect grassTopMiddle{ sf::Vector2i(18, 54), TILE_SIZE };
	sf::IntRect grassTopRight{ sf::Vector2i(36, 54), TILE_SIZE };

	sf::IntRect grassMiddleLeft{ sf::Vector2i(0, 72), TILE_SIZE };
	sf::IntRect grassMiddleMiddle{ sf::Vector2i(18, 72), TILE_SIZE };
	sf::IntRect grassMiddleRight{ sf::Vector2i(36, 72), TILE_SIZE };
	
	sf::IntRect grassBottomLeft{ sf::Vector2i(0, 90), TILE_SIZE };
	sf::IntRect grassBottomMiddle{ sf::Vector2i(18, 90), TILE_SIZE };
	sf::IntRect grassBottomRight{ sf::Vector2i(36, 90), TILE_SIZE };

	sf::IntRect grassCornerBottomLeft{ sf::Vector2i(54, 36), TILE_SIZE };
	sf::IntRect grassCornerBottomRight{ sf::Vector2i(72, 36), TILE_SIZE };
	sf::IntRect grassCornerTopLeft{ sf::Vector2i(54, 54), TILE_SIZE };
	sf::IntRect grassCornerTopRight{ sf::Vector2i(72, 54), TILE_SIZE };
};