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
	WallSliding,
	Dying,
	Reviving
};

enum class CollisionSide {
	None, Top, Bottom, Left, Right
};

struct CollisionResult {
	bool collided;
	CollisionSide side;
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

	void applyVelocityX();
	void applyVelocityY();

	void checkCollisionX(Tile& t_tile);
	void checkCollisionY(Tile& t_tile);
	CollisionResult getCollisionSide(Tile& t_tile);

	void checkNewItem();

	void updateHearts(sf::Vector2f t_viewPos);

	void takeDamage();

	void animate();
	void playAnimationOnce();
	void addFrame(sf::IntRect& t_frame);
	void setFrames();

	void setOnGround(bool t_onGround);
	void setStartPosition(sf::Vector2f t_position);

	std::vector<sf::Sprite>& getHearts();
	sf::Vector2f getPosition();
	PlayerState getState();
	Inventory& getInventory();

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Texture m_reviveTexture;

	sf::Texture m_heartTexture;
	std::vector<sf::Sprite> m_heartSprites;

	sf::RectangleShape m_hitbox;

	int m_maxHealth;
	int m_health;

	sf::Vector2f m_levelStartPosition;

	sf::Vector2f m_position;
	sf::Vector2f m_spritePosition;
	sf::Vector2f m_velocity;
	sf::Vector2f m_speed;

	Inventory m_inventory;

	bool m_hasDoubleJump;
	bool m_doubleJumpReady;

	bool m_onGround;

	PlayerState m_previousState;
	PlayerState m_playerState;
	//std::unique_ptr<PlayerState> m_PlayerState; // Might be used in future for states

	sf::Vector2i m_frameSize;
	std::vector<sf::IntRect> m_playerFrames;
	sf::Time m_playerTime;
	sf::Clock m_playerClock;
	int m_currentPlayerFrame;

};