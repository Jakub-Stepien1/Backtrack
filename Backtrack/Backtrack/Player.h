#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Platform.h"

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

	bool checkGroundCollision(Platform& t_platform);
	void calculateGroundLevel(Platform& t_platform);

	void setGroundLevel(float t_groundLevel);

	sf::Vector2f getPosition();
	PlayerState getState();

private:

	sf::RectangleShape m_hitbox;
	
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_speed;

	float m_groundLevel;

	PlayerState m_playerState;
	//std::unique_ptr<PlayerState> m_PlayerState; // Might be used in future for states

};