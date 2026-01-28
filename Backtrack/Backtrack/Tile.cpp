#include "Tile.h"

Tile::Tile()
{
	sprite.setTexture(texture);

	tileRect = sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(18, 18));

	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineColor(sf::Color(100,100,100));
	rectangle.setSize(sf::Vector2f(18.0f * 2, 18.0f * 2));

	sprite.setScale(sf::Vector2f(2.0f, 2.0f));

	outlineVisible = false;
	empty = true;
}

Tile::~Tile()
{
}


void Tile::render(sf::RenderWindow& t_window)
{
	if (outlineVisible)
	{
		t_window.draw(rectangle);
	}
	if (!empty)
	{
		t_window.draw(sprite);
	}
}

void Tile::setTile(int t_tile, SurroundingTiles t_surrounding)
{
	if (t_tile == 0)
	{
		//rectangle.setFillColor(sf::Color::Transparent);
		tileRect = sf::IntRect(sf::Vector2i(90, 0), sf::Vector2i(18, 18));
		empty = true;
	}
	else
	{
		//rectangle.setFillColor(sf::Color::Black);
		setTextureRect(t_surrounding, t_tile);
		empty = false;
	}
}

void Tile::setPosition(sf::Vector2f t_position)
{
	position = t_position;

	rectangle.setPosition(position);
	sprite.setPosition(position);
}

void Tile::setTexture(sf::Texture& t_texture)
{
	texture = t_texture;
	sprite.setTexture(texture);
	sprite.setTextureRect(tileRect);
}

void Tile::setTextureRect(SurroundingTiles t_surrounding, int t_tileType)
{
	// Top Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_TOP_LEFT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_TOP_LEFT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_TOP_MIDDLE;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_TOP_MIDDLE;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == 0
		&& t_surrounding.top == 0
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_TOP_RIGHT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_TOP_RIGHT;
		}
	}

	// Middle Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_MIDDLE_LEFT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_MIDDLE_LEFT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_MIDDLE_MIDDLE;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_MIDDLE_MIDDLE;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == 0
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_MIDDLE_RIGHT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_MIDDLE_RIGHT;
		}
	}

	// Bottom Layer
	if (t_surrounding.left == 0
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_BOTTOM_LEFT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_BOTTOM_LEFT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_BOTTOM_MIDDLE;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_BOTTOM_MIDDLE;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == 0
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_BOTTOM_RIGHT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_BOTTOM_RIGHT;
		}
	}

	// Corners
	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.bottomLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_CORNER_TOP_RIGHT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_CORNER_TOP_RIGHT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.bottomRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_CORNER_TOP_LEFT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_CORNER_TOP_LEFT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.topLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_CORNER_BOTTOM_RIGHT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_CORNER_BOTTOM_RIGHT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.topRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_CORNER_BOTTOM_LEFT;
		}
		else if (t_tileType == 2)
		{
			tileRect = BRICK_CORNER_BOTTOM_LEFT;
		}
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.topRight == 0
		&& t_surrounding.bottomLeft == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_DIAGONAL_LEFT;
		}
		/*else if (t_tileType == 2)
		{
			tileRect = BRICK_DIAGONAL_LEFT;
		}*/
	}

	if (t_surrounding.left == t_tileType
		&& t_surrounding.right == t_tileType
		&& t_surrounding.top == t_tileType
		&& t_surrounding.bottom == t_tileType
		&& t_surrounding.topLeft == 0
		&& t_surrounding.bottomRight == 0)
	{
		if (t_tileType == 1)
		{
			tileRect = GRASS_DIAGONAL_RIGHT;
		}
		/*else if (t_tileType == 2)
		{
			tileRect = BRICK_DIAGONAL_RIGHT;
		}*/
	}

	sprite.setTextureRect(tileRect);
}

bool Tile::isMouseOver(sf::Vector2i t_mousePos)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(t_mousePos);
	if (rectangle.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		return true;
	}
	return false;
}

void Tile::showOutline(bool t_show)
{
	if (t_show)
	{
		outlineVisible = true;
		rectangle.setOutlineThickness(1.0f);
	}
	else
	{
		outlineVisible = false;
		rectangle.setOutlineThickness(0.0f);
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