#include "Inventory.h"

Inventory::Inventory() : 
	m_inventoryTexture("ASSETS\\IMAGES\\Menus\\Inventory\\inventory.png"),
	m_inventorySprite(m_inventoryTexture)
{
	m_inventorySprite.setOrigin(m_inventorySprite.getGlobalBounds().getCenter());
	m_inventorySprite.setScale(sf::Vector2f(2.0f, 2.0f));
	m_inventorySprite.setPosition(sf::Vector2f(400.0f, 300.0f));
	
	m_itemStartPos = sf::Vector2f( m_inventorySprite.getPosition().x - 27.0f, m_inventorySprite.getPosition().y + 28.0f);
	
	m_itemCount = 0;
}

Inventory::~Inventory()
{
}

void Inventory::update()
{
}

void Inventory::render(sf::RenderWindow& t_window)
{
	t_window.draw(m_inventorySprite);

	for (Item& item : m_items)
	{
		t_window.draw(item.sprite);
	}
}

void Inventory::addItem(sf::Texture* t_item)
{
	m_itemCount++;
	Item newItem(t_item);
	
	if (m_itemCount == 1)
	{
		newItem.name = "Potion of Leaping";
		newItem.description = "Grants the ability to double jump.";
	}

	newItem.sprite.setOrigin(newItem.sprite.getGlobalBounds().getCenter());
	newItem.sprite.setScale(sf::Vector2f(2.0f, 2.0f));
	newItem.sprite.setPosition(m_itemStartPos + sf::Vector2f(m_items.size() * 50.0f, 0.0f));

	m_items.push_back(newItem);
}

int Inventory::getItemCount()
{
	return m_itemCount;
}
