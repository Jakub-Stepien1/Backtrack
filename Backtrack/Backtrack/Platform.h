#pragma once

#include <SFML/Graphics.hpp>

class Platform
{
public:
	Platform();
	Platform(sf::Vector2f t_size, sf::Vector2f t_position);
	~Platform();

	void render(sf::RenderWindow& t_window);

	void activateInRange(sf::Vector2f t_playerPos);

	sf::RectangleShape getShape();
	sf::Vector2f getPosition();
	bool isActive();

private:

	sf::RectangleShape m_shape;
	sf::Vector2f m_position;

	bool m_isActive;
};