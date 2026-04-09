#pragma once

#include "PlayerState.h"
#include "Inventory.h"
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

	void update(sf::Vector2f t_viewPos);
	void render(sf::RenderWindow& t_window);

	void checkInput();
	void checkState();

	void checkCeilingCollisions(Tile& t_tile);
	void checkSideCollisions(Tile& t_tile);
	bool checkGroundCollisions(Tile& t_tile);
	void calculateGroundLevel(Tile& t_tile);

	void setGroundLevel(float t_groundLevel);

	void checkNewItem();

	void updateHearts(sf::Vector2f t_viewPos);

	void animate();
	void playAnimationOnce();
	void addFrame(sf::IntRect& t_frame);
	void setFrames();

	void setToLevelStart();

	std::vector<sf::Sprite>& getHearts();
	sf::Vector2f getPosition();
	PlayerState getState();
	Inventory& getInventory();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::Texture m_heartTexture;
	std::vector<sf::Sprite> m_heartSprites;

	sf::RectangleShape m_hitbox;

	int m_maxHealth;
	int m_health;

	sf::Vector2f m_position;
	sf::Vector2f m_spritePosition;
	sf::Vector2f m_velocity;
	float m_speed;

	Inventory m_inventory;

	bool m_hasDoubleJump;
	bool m_doubleJumpReady;

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