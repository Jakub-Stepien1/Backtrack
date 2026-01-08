#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class MenuButton
{
public:
	MenuButton();
	~MenuButton();

	void setFont(const sf::Font& t_font);
	void setPosition(const sf::Vector2f t_position);
	void setText(const sf::String t_string);

	bool isMouseOver(sf::Vector2i t_mousePos);

	void hover();
	void unhover();

	void render(sf::RenderWindow& t_window);

private:

	sf::RectangleShape rect;
	sf::Font font;
	sf::Text text{ font };
	sf::Vector2f position;
};