#pragma once
#include <SFML/Graphics.hpp>
#include "GlobalConstants.h"

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
	void setTexture(sf::Texture& t_texture);
	void setTextureRect(SurroundingTiles t_surrounding, int t_tileType);

	bool isMouseOver(sf::Vector2i t_mousePos);

	void showOutline(bool t_show);

	sf::Vector2f getPosition();
	sf::Vector2f getCenter();
	sf::RectangleShape getShape();

private:
	sf::Vector2f position;

	sf::Texture texture;
	sf::Sprite sprite{ texture };

	sf::IntRect tileRect;

	sf::RectangleShape rectangle;

	bool outlineVisible;
	bool empty;
};