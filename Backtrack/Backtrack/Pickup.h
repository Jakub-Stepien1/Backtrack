#pragma once

#include <SFML/Graphics.hpp>

class Pickup
{
public:
	Pickup();
	~Pickup();

	void update();
	void render(sf::RenderWindow& t_window);

	bool collidesWithPlayer(sf::Vector2f t_playerPos);

	void setPosition(sf::Vector2f t_position);


private:
	sf::RectangleShape m_shape;

	sf::Vector2f m_position;

};