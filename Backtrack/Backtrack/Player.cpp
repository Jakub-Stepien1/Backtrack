#include "Player.h"

Player::Player()
{
	m_playerState = PlayerState::Idle;

	m_position = sf::Vector2f(100.0f, 400.0f);
	m_speed = 2.0f;

	m_hitbox.setSize(sf::Vector2f(30.0f, 50.0f));
	m_hitbox.setOrigin(m_hitbox.getSize() / 2.0f);
	m_hitbox.setPosition(m_position);
	m_hitbox.setFillColor(sf::Color::White);
	m_hitbox.setOutlineColor(sf::Color::Black);
	m_hitbox.setOutlineThickness(2.0f);

	m_groundLevel = 2000.0f;
}

Player::~Player()
{
}

void Player::update()
{
	checkInput();
	checkState();
}

void Player::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_hitbox);
}

void Player::checkInput()
{
#pragma region Running
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_velocity.x -= 0.4f;
		if (m_playerState != PlayerState::Jumping)
		{
			m_playerState = PlayerState::Running;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_velocity.x += 0.4f;
		if (m_playerState != PlayerState::Jumping)
		{
			m_playerState = PlayerState::Running;
		}
	}

	if (std::abs(m_velocity.x) > 0.05f) // Apply friction
	{
		m_velocity.x *= 0.9f;
	}
	else
	{
		m_velocity.x = 0.0f;
		if (m_playerState != PlayerState::Jumping)
		{
			m_playerState = PlayerState::Idle;
		}
	}
#pragma endregion
#pragma region Jumping
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_playerState != PlayerState::Jumping)
	{
		m_velocity.y = -10.0f;
		m_playerState = PlayerState::Jumping;
	}
	
	if (m_position.y < m_groundLevel)
	{
		m_playerState = PlayerState::Jumping;
	}

	if (m_playerState == PlayerState::Jumping)
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
	case PlayerState::Dashing:
		std::cout << "State: Dashing" << std::endl;
		break;
	default:
		break;
	}
}

bool Player::checkGroundCollision(Platform& t_platform)
{
	sf::Vector2f bottomCenterPlayer = sf::Vector2f(m_hitbox.getPosition().x, m_hitbox.getPosition().y + m_hitbox.getSize().y / 2.0f);

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

sf::Vector2f Player::getPosition()
{
	return m_position;
}

PlayerState Player::getState()
{
	return m_playerState;
}
