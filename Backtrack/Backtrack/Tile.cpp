#include "Tile.h"

Tile::Tile()
{
	sprite.setTexture(texture);

	tileRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(18, 18));

	rectangle.setFillColor(sf::Color::Transparent);
	//rectangle.setOutlineColor(sf::Color::Black);
	//rectangle.setOutlineThickness(2.0f);
	rectangle.setSize(sf::Vector2f(18.0f * 2, 18.0f * 2));

	sprite.setScale(sf::Vector2f(2.0f, 2.0f));
}

Tile::~Tile()
{
}


void Tile::render(sf::RenderWindow& t_window)
{
	//t_window.draw(rectangle);
	t_window.draw(sprite);
}

void Tile::setTile(int t_tile, SurroundingTiles t_surrounding)
{
	switch (t_tile)
	{
	case 0:
		rectangle.setFillColor(sf::Color::Transparent);
		tileRect = sf::IntRect(sf::Vector2i(54, 90), sf::Vector2i(18, 18));
		break;
	case 1:
		rectangle.setFillColor(sf::Color::Black);

		// Top Layer
		if (t_surrounding.left == 0
			&& t_surrounding.right == 1
			&& t_surrounding.top == 0
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassTopLeft;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 1
			&& t_surrounding.top == 0
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassTopMiddle;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 0
			&& t_surrounding.top == 0
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassTopRight;
		}

		// Middle Layer
		if (t_surrounding.left == 0
			&& t_surrounding.right == 1
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassMiddleLeft;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 1
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassMiddleMiddle;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 0
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 1)
		{
			tileRect = grassMiddleRight;
		}

		// Bottom Layer
		if (t_surrounding.left == 0
			&& t_surrounding.right == 1
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 0)
		{
			tileRect = grassBottomLeft;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 1
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 0)
		{
			tileRect = grassBottomMiddle;
		}

		if (t_surrounding.left == 1
			&& t_surrounding.right == 0
			&& t_surrounding.top == 1
			&& t_surrounding.bottom == 0)
		{
			tileRect = grassBottomRight;
		}

		break;
	default:
		break;
	}
}

void Tile::setPosition(sf::Vector2f t_position)
{
	rectangle.setPosition(t_position);
	sprite.setPosition(t_position);
}

void Tile::setTexture(const sf::Texture& t_texture)
{
	texture = t_texture;
	sprite.setTexture(texture);
	sprite.setTextureRect(tileRect);
}
