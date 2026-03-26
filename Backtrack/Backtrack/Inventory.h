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

	void update();
	void render(sf::RenderWindow& t_window);

	void addItem(sf::Texture* t_item);

	int getItemCount();

private:

	int m_itemCount;

	sf::Texture m_inventoryTexture;
	sf::Sprite m_inventorySprite;
	
	std::vector<Item> m_items;

	sf::Vector2f m_itemStartPos;
};