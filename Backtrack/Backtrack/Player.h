#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "PlayerState.h"
#include "Tile.h"

enum class PlayerState
{
	None,
	Idle,
	Running,
	Jumping,
	Falling,
	Dashing,
	Sliding,
	WallSliding
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

	void checkCeilingCollisions(Tile& t_tile);
	void checkSideCollisions(Tile& t_tile);
	bool checkGroundCollisions(Tile& t_tile);
	void calculateGroundLevel(Tile& t_tile);

	void setGroundLevel(float t_groundLevel);

	void animate();
	void playAnimationOnce();
	void addFrame(sf::IntRect& t_frame);
	void setFrames();

	sf::Vector2f getPosition();
	PlayerState getState();

private:
	const float SCALE_FACTOR = 2.0f;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::RectangleShape m_hitbox;

	sf::Vector2f m_position;
	sf::Vector2f m_spritePosition;
	sf::Vector2f m_velocity;
	float m_speed;

	float m_groundLevel;

	PlayerState m_previousState;
	PlayerState m_playerState;
	//std::unique_ptr<PlayerState> m_PlayerState; // Might be used in future for states

	sf::Vector2i m_frameSize;
	std::vector<sf::IntRect> m_playerFrames;
	sf::Time m_playerTime;
	sf::Clock m_playerClock;
	int m_currentPlayerFrame;

};