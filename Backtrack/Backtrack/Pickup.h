#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pickup
{
public:
	Pickup();
	~Pickup();

	void update(sf::Clock t_gameTime);
	void render(sf::RenderWindow& t_window);

	void passTexture(sf::Texture& t_texture);
	void setPosition(sf::Vector2f t_position);

	bool collidesWithPlayer(sf::Vector2f t_playerPos);

	sf::Texture* getTexture();
private:
	sf::RectangleShape m_shape;

	sf::Texture* m_texture{ nullptr };
	std::optional<sf::Sprite> m_sprite;

	sf::Vector2f m_position;

	float bobbingSpeed = 5.0f;
	float bobbingHeight = 5.0f;
};