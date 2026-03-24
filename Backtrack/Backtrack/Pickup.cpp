#include "Pickup.h"

Pickup::Pickup()
{
	m_position = sf::Vector2f(200.0f, 400.0f);

	m_shape.setSize(sf::Vector2f(32.0f, 32.0f));
	m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
	m_shape.setPosition(m_position);
}

Pickup::~Pickup()
{
}

void Pickup::update()
{
}

void Pickup::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

bool Pickup::collidesWithPlayer(sf::Vector2f t_playerPos)
{
	bool collision = false;

	float distance = sqrt(pow(m_position.x - t_playerPos.x, 2) + pow(m_position.y - t_playerPos.y, 2));
	
	if (distance < 40.0f)
	{
		collision = true;
	}
	
	return collision;
}

void Pickup::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_shape.setPosition(m_position);
}