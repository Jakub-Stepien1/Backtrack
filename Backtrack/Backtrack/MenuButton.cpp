#include "MenuButton.h"

MenuButton::MenuButton()
{
	position = sf::Vector2f(200.0f, 50.0f);

	text.setFont(font);
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::White);
	text.setOutlineColor(sf::Color::Black);
	text.setOutlineThickness(2.0f);
	text.setPosition(position);

	rect.setSize(sf::Vector2f(400.0f, 100.0f));
	rect.setOrigin(rect.getSize() / 2.0f);
	rect.setFillColor(sf::Color::White);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(4.0f);
	rect.setPosition(position);

}

MenuButton::~MenuButton()
{
}

void MenuButton::setFont(const sf::Font& t_font)
{
	font = t_font;
	text.setFont(font);
}

void MenuButton::setPosition(const sf::Vector2f t_position)
{
	position = t_position;
	text.setPosition(position);
	rect.setPosition(position);
}

void MenuButton::setText(const sf::String t_string)
{
	text.setString(t_string);
	text.setOrigin(text.getLocalBounds().getCenter());
}

bool MenuButton::isMouseOver(sf::Vector2i t_mousePos)
{
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(t_mousePos);
	if (rect.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
	{
		return true;
	}
	return false;
}

void MenuButton::hover()
{
	float scaleFactor = 1.1f;
	
	if (rect.getScale().x < scaleFactor)
	{
		rect.setFillColor(sf::Color(210, 210, 210));

		rect.scale(sf::Vector2f(1.02f, 1.02f));
		text.scale(sf::Vector2f(1.02f, 1.02f));
	}
}

void MenuButton::unhover()
{
	float scaleFactor = 1.0f;

	if (rect.getScale().x > scaleFactor)
	{
		rect.setFillColor(sf::Color::White);

		rect.scale(sf::Vector2f(0.99f, 0.99f));
		text.scale(sf::Vector2f(0.99f, 0.99f));
	}
}

void MenuButton::render(sf::RenderWindow& t_window)
{
	t_window.draw(rect);
	t_window.draw(text);
}