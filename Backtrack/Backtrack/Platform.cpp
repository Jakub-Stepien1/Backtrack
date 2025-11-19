#include "Platform.h"

Platform::Platform()
{
	m_position = sf::Vector2f(400.0f, 600.0f);

	m_shape.setSize(sf::Vector2f(600.0f, 50.0f));
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
	m_shape.setFillColor(sf::Color::Black);
	m_shape.setPosition(m_position);

	m_isActive = false;
}

Platform::Platform(sf::Vector2f t_size, sf::Vector2f t_position)
{
	m_position = t_position;

	m_shape.setSize(t_size);
	m_shape.setOrigin(m_shape.getSize() / 2.0f);
	m_shape.setFillColor(sf::Color::Black);
	m_shape.setPosition(m_position);

	m_isActive = false;
}

Platform::~Platform()
{
}

void Platform::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

void Platform::activateInRange(sf::Vector2f t_playerPos)
{
	float distance = sqrt(pow(t_playerPos.x - m_position.x, 2) + pow(t_playerPos.y - m_position.y, 2));
	if (distance < 800.0f)
	{
		m_isActive = true;
	}
	else
	{
		m_isActive = false;
	}
}

sf::RectangleShape Platform::getShape()
{
	return m_shape;
}

sf::Vector2f Platform::getPosition()
{
	return m_position;
}

bool Platform::isActive()
{
	return m_isActive;
}
