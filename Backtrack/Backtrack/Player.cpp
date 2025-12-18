#include "Player.h"

Player::Player() : 
	m_texture("ASSETS\\IMAGES\\all48x61-playerSheet.png"),
	m_sprite(m_texture)
{
	m_frameSize = sf::Vector2i(48, 61);
	m_playerTime = sf::seconds(0.15f);
	m_currentPlayerFrame = 0;

	m_previousState = PlayerState::None;
	m_playerState = PlayerState::Idle;

	m_position = sf::Vector2f(100.0f, 400.0f);
	m_spritePosition = sf::Vector2f(m_position.x + 6.0f, m_position.y - 6.0f);
	m_speed = 2.0f;

	m_hitbox.setSize(sf::Vector2f(30.0f, 50.0f));
	m_hitbox.setOrigin(m_hitbox.getSize() / 2.0f);
	m_hitbox.setPosition(m_position);
	m_hitbox.setFillColor(sf::Color::Transparent);
	m_hitbox.setOutlineColor(sf::Color::Green);
	m_hitbox.setOutlineThickness(2.0f);

	m_groundLevel = 2000.0f;

	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0.0f, 0.0f), m_frameSize));
	m_sprite.setOrigin(sf::Vector2f(48.0f / 2.0f, 61.0f / 2.0f));
	m_sprite.setPosition(m_spritePosition);
	m_sprite.setScale(sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR));
}

Player::~Player()
{
}

void Player::update()
{
	checkInput();
	//checkState();

	if (m_playerState != m_previousState)
	{
		setFrames();
	}

	if (m_playerState != PlayerState::Jumping)
	{
		animate();
	}
	else
	{
		playAnimationOnce();
	}
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_hitbox);
	t_window.draw(m_sprite);	
}

void Player::checkInput()
{
#pragma region Running
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_sprite.setScale(sf::Vector2f(-SCALE_FACTOR, SCALE_FACTOR)); // Flip sprite left
		m_velocity.x -= 0.5f;
		if (m_playerState != PlayerState::Jumping 
			&& m_playerState != PlayerState::Falling)
		{
			m_playerState = PlayerState::Running;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_sprite.setScale(sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR)); // Flip sprite right
		m_velocity.x += 0.5f;
		if (m_playerState != PlayerState::Jumping 
			&& m_playerState != PlayerState::Falling)
		{
			m_playerState = PlayerState::Running;
		}
	}

#pragma endregion
#pragma region Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) 
		&& m_playerState != PlayerState::Jumping 
		&& m_playerState != PlayerState::Falling)
	{
		m_velocity.y = -10.0f;
		m_playerState = PlayerState::Jumping;
	}
	
	if (m_position.y < m_groundLevel)
	{
		if (m_velocity.y < 0.0f)
		{
			m_playerState = PlayerState::Jumping;
		}
		else
		{
			m_playerState = PlayerState::Falling;
		}
	}

	if (m_playerState == PlayerState::Jumping || m_playerState == PlayerState::Falling)
	{
		if (m_velocity.y < 8.0f)
		{
			m_velocity.y += 0.4f; // Apply gravity	
		}
		
		if (m_position.y > m_groundLevel)
		{
			if (m_groundLevel == 2000.0f)
			{
				m_position.y = 400.0f;
			}
			else
			{
				m_position.y = m_groundLevel;
			}
			
			m_velocity.y = 0.0f;
			m_playerState = PlayerState::Idle;
		}
	}
#pragma endregion
	
	m_position += m_velocity;
	m_hitbox.setPosition(m_position);

	m_spritePosition = sf::Vector2f(m_position.x, m_position.y - 6.0f);
	m_sprite.setPosition(m_spritePosition);


	if (std::abs(m_velocity.x) > 0.05f) // Apply friction
	{
		m_velocity.x *= 0.8f;
	}
	else
	{
		m_velocity.x = 0.0f;
		if (m_playerState != PlayerState::Jumping && m_playerState != PlayerState::Falling)
		{
			m_playerState = PlayerState::Idle;
		}
	}
	//std::cout << m_velocity.x << std::endl;
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
	default:
		break;
	}
}

bool Player::checkGroundCollision(Platform& t_platform)
{
	sf::Vector2f bottomCenterPlayer = sf::Vector2f(m_position.x, m_position.y + m_hitbox.getSize().y / 2.0f);
	bottomCenterPlayer += m_velocity;

	if (t_platform.getShape().getGlobalBounds().contains(bottomCenterPlayer))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::calculateGroundLevel(Platform& t_platform)
{
	m_groundLevel = t_platform.getPosition().y - t_platform.getShape().getSize().y / 2.0f - m_hitbox.getSize().y / 2.0f;
}

void Player::setGroundLevel(float t_groundLevel)
{
	m_groundLevel = t_groundLevel;
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
	default:
		break;
	}
}

sf::Vector2f Player::getPosition()
{
	return m_position;
}

PlayerState Player::getState()
{
	return m_playerState;
}
