#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

struct Item
{
	std::string name;
	std::string description;
	sf::Texture* texture;
	sf::Sprite sprite;

	Item(sf::Texture* t_texture) :
		texture(t_texture),
		sprite(*texture)
	{}
};

class Inventory
{
public:
	Inventory();
	~Inventory();

	void update(sf::RenderWindow& t_window);
	void render(sf::RenderWindow& t_window);

	void addItem(sf::Texture* t_item);
	void centreOnScreen(sf::Vector2f t_viewPosition);

	int getItemCount();

private:

	int m_itemCount;

	sf::RectangleShape m_inventoryBackground;
	
	sf::Texture m_inventoryTexture;
	sf::Sprite m_inventorySprite;

	sf::Texture m_highlightTexture;
	sf::Sprite m_highlightSprite;
	
	sf::Vector2f m_position;

	std::vector<Item> m_items;

	sf::Vector2f m_highlightPos;
	sf::Vector2f m_itemStartPos;
	float m_itemOffset;

	bool m_hoveringItem;

	sf::Font m_font;
	sf::Text m_itemNameText;
	sf::Text m_itemDescriptionText;

	sf::Vector2f m_textPosition;
};