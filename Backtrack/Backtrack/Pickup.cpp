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

void Pickup::update(sf::Clock t_gameTime)
{
	float newYPos = m_position.y + sin(static_cast<float>(t_gameTime.getElapsedTime().asSeconds()) * bobbingSpeed) * bobbingHeight; // Sine wave formula for bobbing effect
	m_sprite->setPosition(sf::Vector2f(m_position.x, newYPos));
}

void Pickup::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_shape);
	t_window.draw(*m_sprite);
}

void Pickup::passTexture(sf::Texture& t_texture)
{
	m_texture = &t_texture;
	m_sprite.emplace(*m_texture);
	m_sprite->setOrigin(m_sprite->getGlobalBounds().getCenter());
	m_sprite->setScale(sf::Vector2f(2.0f, 2.0f));
}

void Pickup::setPosition(sf::Vector2f t_position)
{
	m_position = t_position;
	m_shape.setPosition(m_position);
	m_sprite->setPosition(m_position);
}

bool Pickup::collidesWithPlayer(sf::Vector2f t_playerPos)
{
	bool collision = false;

	float distance = sqrt(pow(m_position.x - t_playerPos.x, 2) + pow(m_position.y - t_playerPos.y, 2));

	if (distance < 50.0f)
	{
		collision = true;
	}

	return collision;
}

sf::Texture* Pickup::getTexture()
{ 
	return m_texture; 
}