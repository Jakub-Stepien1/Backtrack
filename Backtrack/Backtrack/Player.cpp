#include "Player.h"

Player::Player() : 
	m_texture("ASSETS\\IMAGES\\Characters\\all48x61-playerSheet.png"),
	m_sprite(m_texture),
	m_heartTexture("ASSETS\\IMAGES\\Items\\Hearts\\hearts.png"),
	m_reviveTexture("ASSETS\\IMAGES\\Characters\\star-Sheet91px.png")
{
	m_frameSize = sf::Vector2i(48, 61);
	m_playerTime = sf::seconds(0.15f);
	m_currentPlayerFrame = 0;

	m_previousState = PlayerState::None;
	m_playerState = PlayerState::Idle;

	m_maxHealth = 2;
	m_health = m_maxHealth;

	m_position = sf::Vector2f(200.0f, 600.0f);
	m_spritePosition = sf::Vector2f(m_position.x + 6.0f, m_position.y - 6.0f);
	m_speed = sf::Vector2f(2.0f, 1.0f);

	m_hitbox.setSize(sf::Vector2f(60.0f, 90.0f));
	m_hitbox.setOrigin(m_hitbox.getSize() / 2.0f);
	m_hitbox.setPosition(m_position);
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(2.0f);

	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0.0f, 0.0f), m_frameSize));
	m_sprite.setOrigin(sf::Vector2f(48.0f / 2.0f, 61.0f / 2.0f));
	m_sprite.setPosition(m_spritePosition);
	m_sprite.setScale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));

	for (int i = 0; i < m_maxHealth; i++)
	{
		sf::Sprite heartContainer{ m_heartTexture };
		heartContainer.setTextureRect(HEART_EMPTY);
		heartContainer.setOrigin(heartContainer.getGlobalBounds().getCenter());
		heartContainer.setPosition(sf::Vector2f(m_position.x - 100.0f + i * 60.0f, m_position.y - 100.0f));
		heartContainer.setScale(sf::Vector2f(3.0f, 3.0f));
		m_heartSprites.push_back(heartContainer);
	}
	
	m_onGround = false;

	m_doubleJumpReady = false;
	m_hasDoubleJump = false;

	m_dashReady = false;
	m_hasDash = true;
	m_dashDuration = sf::seconds(0.2f);
	m_dashCooldown = sf::seconds(2.0f);
}

Player::~Player()
{
}

void Player::update(sf::Vector2f t_viewPos)
{
	checkState();
	if (m_position.y > 1000.0f)
	{
		m_position.y = 400.0f;
	}
	if (m_position.x < 32.0f)
	{
		m_position.x = 32.0f;
		m_sprite.setPosition(sf::Vector2f(32.0f, m_sprite.getPosition().y));
	}

	updateHearts(t_viewPos);

	if (m_playerState != m_previousState)
	{
		setFrames();
	}

	if (m_playerState == PlayerState::Jumping
		|| m_playerState == PlayerState::Reviving
		|| m_playerState == PlayerState::Dying)
	{
		playAnimationOnce();
	}
	else
	{
		animate();
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	//t_window.draw(m_hitbox);
	t_window.draw(m_sprite);	

	for (const sf::Sprite& heart : m_heartSprites)
	{
		t_window.draw(heart);
	}
}

void Player::checkInput()
{
	if (m_playerState != PlayerState::Reviving
		&& m_playerState != PlayerState::Dying)
	{
#pragma region Running
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			m_sprite.setScale(sf::Vector2f(-PLAYER_SCALE, PLAYER_SCALE)); // Flip sprite left
			m_velocity.x -= 0.5f;
			if (m_onGround)
			{
				m_playerState = PlayerState::Running;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			m_sprite.setScale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE)); // Flip sprite right
			m_velocity.x += 0.5f;
			if (m_onGround)
			{
				m_playerState = PlayerState::Running;
			}
		}

#pragma endregion
#pragma region Jumping
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
			&& m_playerState != PlayerState::Jumping
			&& m_playerState != PlayerState::Falling
			&& m_playerState != PlayerState::Dashing)
		{
			m_playerState = PlayerState::Jumping;
			m_velocity.y = -10.0f;
		}

		if (m_hasDoubleJump)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)
				&& m_playerState != PlayerState::Jumping
				&& m_playerState != PlayerState::Dashing
				&& m_doubleJumpReady)
			{
				m_playerState = PlayerState::Jumping;
				m_velocity.y = -10.0f;
				m_doubleJumpReady = false;
			}
		}

		if (!m_onGround
			&& m_playerState != PlayerState::Dashing)
		{
			if (m_velocity.y < 8.0f)
			{
				m_velocity.y += 0.4f; // Apply gravity	
			}

			if (m_velocity.y < 0.0f)
			{
				m_playerState = PlayerState::Jumping;
			}
			else
			{
				m_playerState = PlayerState::Falling;
			}
		}
#pragma endregion

		if (std::abs(m_velocity.x) > 0.05f) // Apply friction
		{
			m_velocity.x *= 0.8f;
			if (m_onGround)
			{
				m_playerState = PlayerState::Running;
			}
		}
		else
		{
			m_velocity.x = 0.0f;
			if (m_onGround)
			{
				m_playerState = PlayerState::Idle;
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift)
			&& m_hasDash
			&& m_dashReady)
		{
			m_playerState = PlayerState::Dashing;
			if (m_sprite.getScale().x > 0)
			{
				m_velocity.x += 5.0f;
			}
			else
			{
				m_velocity.x -= 5.0f;
			}
			m_velocity.y = 0.0f;
			m_dashReady = false;
			m_dashDurationClock.restart();
			m_dashCooldownClock.restart();
		}

		if (m_dashCooldownClock.getElapsedTime() > m_dashCooldown)
		{
			m_dashReady = true;
		}

		if (m_playerState == PlayerState::Dashing)
		{
			applyVelocityX();
			applyVelocityY();
			if (m_dashDurationClock.getElapsedTime() >= m_dashDuration)
			{
				m_playerState = PlayerState::Falling;
			}
		}
	}
}

void Player::checkState()
{
	switch (m_playerState)
	{
	case PlayerState::Idle:
		std::cout << "State: Idle" << std::endl;
		break;
	case PlayerState::Running:
		std::cout << "State: Running" << std::endl;
		break;
	case PlayerState::Jumping:
		std::cout << "State: Jumping" << std::endl;
		break;
	case PlayerState::Falling:
		std::cout << "State: Falling" << std::endl;
		break;
	case PlayerState::Dashing:
		std::cout << "State: Dashing" << std::endl;
		break;
	case PlayerState::Dying:
		std::cout << "State: Dying" << std::endl;
		break;
	case PlayerState::Reviving:
		std::cout << "State: Reviving" << std::endl;
		break;
	default:
		break;
	}
}

void Player::applyVelocityX()
{
	m_position.x += m_velocity.x * m_speed.x;
	m_hitbox.setPosition(m_position);
	m_spritePosition = sf::Vector2f(m_position.x + 2.0f, m_position.y - 6.0f);
	m_sprite.setPosition(m_spritePosition);
}

void Player::applyVelocityY()
{
	m_position.y += m_velocity.y * m_speed.y;
	m_hitbox.setPosition(m_position);
	m_spritePosition = sf::Vector2f(m_position.x + 2.0f, m_position.y - 6.0f);
	m_sprite.setPosition(m_spritePosition);
}

void Player::checkCollisionX(Tile& t_tile)
{
	CollisionResult collision = getCollisionSide(t_tile);
	if (collision.collided)
	{
		sf::Vector2f halfTileSize = t_tile.getShape().getGlobalBounds().size / 2.0f;
		sf::Vector2f halfPlayerSize = m_hitbox.getGlobalBounds().size / 2.0f;

		if (collision.side == CollisionSide::Left)
		{
			m_position.x = t_tile.getCenter().x - halfTileSize.x - halfPlayerSize.x;
			m_velocity.x = 0.0f;
		}
		else if (collision.side == CollisionSide::Right)
		{
			m_position.x = t_tile.getCenter().x + halfTileSize.x + halfPlayerSize.x;
			m_velocity.x = 0.0f;
		}

		if (t_tile.isHarmful())
		{
			sf::Vector2f direction = (m_position - t_tile.getCenter()).normalized();
			m_velocity = direction * 10.0f; // Knockback velocity
			m_position += m_velocity; // Apply knockback immediately to prevent sticking to the tile
			takeDamage();
		}
	}
	
	m_hitbox.setPosition(m_position);
}

void Player::checkCollisionY(Tile& t_tile)
{
	CollisionResult collision = getCollisionSide(t_tile);
	if (collision.collided)
	{
		sf::Vector2f halfTileSize = t_tile.getShape().getGlobalBounds().size / 2.0f;
		sf::Vector2f halfPlayerSize = m_hitbox.getGlobalBounds().size / 2.0f;

		if (collision.side == CollisionSide::Top)
		{
			m_position.y = t_tile.getCenter().y - halfTileSize.y - halfPlayerSize.y;
			m_velocity.y = 0.0f;
			m_onGround = true;
			m_doubleJumpReady = true;
			if (m_playerState != PlayerState::Reviving
				&& m_playerState != PlayerState::Dying
				&& m_playerState != PlayerState::Dashing)
			{
				if (std::abs(m_velocity.x) > 0.05f)
					m_playerState = PlayerState::Running;
				else
					m_playerState = PlayerState::Idle;
			}
		}
		else if (collision.side == CollisionSide::Bottom)
		{
			m_position.y = t_tile.getCenter().y + halfTileSize.y + halfPlayerSize.y;
			m_velocity.y = 0.0f;
		}

		if (t_tile.isHarmful())
		{
			sf::Vector2f direction = (m_position - t_tile.getCenter()).normalized();
			m_velocity = direction * 10.0f; // Knockback velocity
			m_position += m_velocity; // Apply knockback immediately to prevent sticking to the tile
			takeDamage();
		}
	}
	m_hitbox.setPosition(m_position);
}

CollisionResult Player::getCollisionSide(Tile& t_tile)
{
	CollisionResult result = { false, CollisionSide::None };

	sf::FloatRect playerBounds = m_hitbox.getGlobalBounds();
	sf::FloatRect tileBounds = t_tile.getShape().getGlobalBounds();

	if (playerBounds.findIntersection(tileBounds))
	{
		result.collided = true;
		auto intersection = playerBounds.findIntersection(tileBounds);

		float overlapX = intersection->size.x;
		float overlapY = intersection->size.y;

		if (overlapX < overlapY) // Smaller X overlap = side collision
		{
			if (playerBounds.getCenter().x < tileBounds.getCenter().x)
			{
				result.side = CollisionSide::Left;
			}
			else
			{
				result.side = CollisionSide::Right;
			}
		}
		else // Smaller Y overlap = top/bottom collision
		{
			if (playerBounds.getCenter().y < tileBounds.getCenter().y)
			{
				result.side = CollisionSide::Top;
			}
			else
			{
				result.side = CollisionSide::Bottom;
			}
		}
	}

	return result;
}

void Player::checkNewItem()
{
	int itemCount = m_inventory.getItemCount();
	switch (itemCount)
	{
		case 1:
			std::cout << "Key item collected: " << itemCount << "\tSpeed\n";
			m_speed.x = 2.5f;
			break;
		case 2:
			std::cout << "Key item collected: " << itemCount << "\tDouble Jump\n";
			m_hasDoubleJump = true;
			break;
		case 3: 
			std::cout << "Key item collected: " << itemCount << "\tDash\n";
			//TO BE ADDED
			break;
		default:
			break;
	}
}

void Player::updateHearts(sf::Vector2f t_viewPos)
{
	float offset = 0.0f;
	for (sf::Sprite& heart : m_heartSprites)
	{
		heart.setPosition(sf::Vector2f(t_viewPos.x - 500.0f + offset * 50.0f, t_viewPos.y - 250.0f));
		offset++;
	}

	for (int i = 0; i < m_maxHealth; i++)
	{
		if (i < m_health)
		{
			m_heartSprites[i].setTextureRect(HEART_FULL);
		}
		else
		{
			m_heartSprites[i].setTextureRect(HEART_EMPTY);
		}
	}
}

void Player::takeDamage()
{
	if (m_health > 0)
	{
		m_health -= 1;
	}

	if (m_health <= 0)
	{
		m_playerState = PlayerState::Dying;
		m_velocity = sf::Vector2f(0.0f, 0.0f);
	}
}

void Player::animate()
{
	if (!m_playerFrames.empty())
	{
		if (m_playerClock.getElapsedTime() > m_playerTime)
		{
			if (m_currentPlayerFrame + 1 < m_playerFrames.size())
			{
				m_currentPlayerFrame++;
			}
			else
			{
				m_currentPlayerFrame = 0;
			}

			m_playerClock.restart();
		}

		m_sprite.setTextureRect(m_playerFrames[m_currentPlayerFrame]);
		m_previousState = m_playerState;
	}
}

void Player::playAnimationOnce()
{
	if (!m_playerFrames.empty())
	{
		if (m_playerClock.getElapsedTime() > m_playerTime)
		{
			if (m_currentPlayerFrame + 1 < m_playerFrames.size())
			{
				m_currentPlayerFrame++;
			}
			else 
			{
				if (m_playerState == PlayerState::Reviving)
				{
					m_playerState = PlayerState::Idle;
					m_sprite.setTexture(m_texture);
					m_sprite.setOrigin(sf::Vector2f(48.0f / 2.0f, 61.0f / 2.0f));
					m_sprite.setScale(sf::Vector2f(PLAYER_SCALE, PLAYER_SCALE));
					setFrames();
				}
				if (m_playerState == PlayerState::Dying)
				{
					m_playerState = PlayerState::Reviving;
					m_health = m_maxHealth;
					m_position = m_levelStartPosition;
					m_hitbox.setPosition(m_position);
					m_spritePosition = sf::Vector2f(m_position.x + 2.0f, m_position.y - 6.0f);
					m_sprite.setPosition(m_spritePosition);
					setFrames();
				}
				
			}

			m_playerClock.restart();
		}

		m_sprite.setTextureRect(m_playerFrames[m_currentPlayerFrame]);
		m_previousState = m_playerState;
	}
}

void Player::addFrame(sf::IntRect& t_frame)
{
	m_playerFrames.push_back(t_frame);
}

void Player::setFrames()
{
	m_playerFrames.clear();
	m_currentPlayerFrame = 0;

	switch (m_playerState)
	{
	case PlayerState::None:
		break;
	case PlayerState::Idle:
		m_playerTime = sf::seconds(0.3f);
		addFrame(sf::IntRect(sf::Vector2i(0, 0), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(48, 0), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(96, 0), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(144, 0), m_frameSize));
		break;
	case PlayerState::Running:
		m_playerTime = sf::seconds(0.2f);
		addFrame(sf::IntRect(sf::Vector2i(192, 0), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(0, 61), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(48, 61), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(96, 61), m_frameSize));
		break;
	case PlayerState::Jumping:
		m_playerTime = sf::seconds(0.3f);
		addFrame(sf::IntRect(sf::Vector2i(144, 61), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(192, 61), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(0, 122), m_frameSize));
		break;
	case PlayerState::Falling:
		m_playerTime = sf::seconds(0.15f);
		addFrame(sf::IntRect(sf::Vector2i(48, 122), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(96, 122), m_frameSize));
		break;
	case PlayerState::Dashing:
		m_playerTime = sf::seconds(0.2f);
		addFrame(sf::IntRect(sf::Vector2i(144, 122), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(192, 122), m_frameSize));
		break;
	case PlayerState::Sliding:
		m_playerTime = sf::seconds(0.2f);
		addFrame(sf::IntRect(sf::Vector2i(0, 183), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(48, 183), m_frameSize));
		break;
	case PlayerState::WallSliding:
		m_playerTime = sf::seconds(0.2f);
		addFrame(sf::IntRect(sf::Vector2i(96, 183), m_frameSize));
		addFrame(sf::IntRect(sf::Vector2i(144, 183), m_frameSize));
		break;
	case PlayerState::Dying:
		m_playerTime = sf::seconds(0.10f);
		m_sprite.setTexture(m_reviveTexture);
		for (int i = 0; i < 9; i++)
		{
			addFrame(sf::IntRect(sf::Vector2i((9 - i) * 91, 0), sf::Vector2i(91, 91)));
		}
		m_sprite.setOrigin(sf::Vector2f(91.0f / 2.0f, 91.0f / 2.0f));
		m_sprite.setScale(sf::Vector2f(1.0f, 1.0f));
		break;
	case PlayerState::Reviving:
		m_playerTime = sf::seconds(0.10f);
		for (int i = 0; i < 9; i++)
		{
			addFrame(sf::IntRect(sf::Vector2i(i * 91, 0), sf::Vector2i(91, 91)));
		}
		break;
	default:
		break;
	}
}

void Player::setOnGround(bool t_onGround)
{
	m_onGround = t_onGround;
}

void Player::setStartPosition(sf::Vector2f t_position)
{
	m_levelStartPosition = t_position;

	m_position = t_position;
	m_hitbox.setPosition(m_position);
	m_spritePosition = sf::Vector2f(m_position.x + 2.0f, m_position.y - 6.0f);
	m_sprite.setPosition(m_spritePosition);
}

std::vector<sf::Sprite>& Player::getHearts()
{
	return m_heartSprites;
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

PlayerState Player::getState()
{
	return m_playerState;
}

Inventory& Player::getInventory()
{
	return m_inventory;
}
