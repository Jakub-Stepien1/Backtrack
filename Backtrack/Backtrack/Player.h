#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerState.h"

enum class PlayerState
{
	Idle,
	Running,
	Jumping,
	Dashing
};

class Player
{
public:
	Player();
	~Player();

	void update();
	void render(sf::RenderWindow& t_window);

	void checkInput();
	void checkState();

private:

	sf::RectangleShape m_hitbox;
	
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_speed;

	PlayerState m_playerState;
	//std::unique_ptr<PlayerState> m_PlayerState; // Might be used in future for states

};