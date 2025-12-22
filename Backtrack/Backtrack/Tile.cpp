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
	t_window.draw(rectangle);
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

		setTextureRect(t_surrounding, t_tile);

		break;
	default:
		break;
	}
}

void Tile::setPosition(sf::Vector2f t_position)
{
	position = t_position;

	rectangle.setPosition(position);
	sprite.setPosition(position);
}

void Tile::setTexture(const sf::Texture& t_texture)
{
	texture = t_texture;
	sprite.setTexture(texture);
	sprite.setTextureRect(tileRect);
}

void Tile::setTextureRect(SurroundingTiles t_surrounding, int t_tileType)
{
	// Top Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == 1
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassTopLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassTopMiddle;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 0
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassTopRight;
		}
	}

	// Middle Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassMiddleLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassMiddleMiddle;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 0
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1)
	{
		if (t_tileType == 1)
		{
			tileRect = grassMiddleRight;
		}
	}

	// Bottom Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassBottomLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassBottomMiddle;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 0
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassBottomRight;
		}
	}

	// Corners
	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.bottomLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassCornerTopRight;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.bottomRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassCornerTopLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.topLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassCornerBottomRight;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.topRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassCornerBottomLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.topRight == 0
		&& t_surrounding.bottomLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassDiagonalLeft;
		}
	}

	if (t_surrounding.left == 1
		&& t_surrounding.right == 1
		&& t_surrounding.top == 1
		&& t_surrounding.bottom == 1
		&& t_surrounding.topLeft == 0
		&& t_surrounding.bottomRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = grassDiagonalRight;
		}
	}
}

sf::Vector2f Tile::getPosition()
{
	return position;
}

sf::RectangleShape Tile::getShape()
{
	return rectangle;
}