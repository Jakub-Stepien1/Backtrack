#include "Inventory.h"

Inventory::Inventory() : 
	m_inventoryTexture("ASSETS\\IMAGES\\Menus\\Inventory\\inventory.png"),
	m_inventorySprite(m_inventoryTexture),
	m_highlightTexture("ASSETS\\IMAGES\\Menus\\Inventory\\highlight.png"),
	m_highlightSprite(m_highlightTexture),
	m_font("ASSETS\\FONTS\\PressStart2P-Regular.ttf"),
	m_itemNameText(m_font),
	m_itemDescriptionText(m_font)
{
	m_position = sf::Vector2f(400.0f, 300.0f);
	m_itemStartPos = sf::Vector2f(m_position.x - 44.0f, m_position.y + 54.0f);
	m_itemOffset = 81.0f;

	m_inventoryBackground.setSize(sf::Vector2f(1368.0f, 768.0f));
	m_inventoryBackground.setOrigin(m_inventoryBackground.getSize() / 2.0f);
	m_inventoryBackground.setFillColor(sf::Color(0, 0, 0, 160));
	m_inventoryBackground.setPosition(m_position);

	m_inventorySprite.setOrigin(m_inventorySprite.getGlobalBounds().getCenter());
	m_inventorySprite.setScale(sf::Vector2f(3.0f, 3.0f));
	m_inventorySprite.setPosition(m_position);

	m_highlightSprite.setOrigin(m_highlightSprite.getGlobalBounds().getCenter());
	m_highlightSprite.setScale(sf::Vector2f(3.0f, 3.0f));
	m_highlightSprite.setPosition(m_itemStartPos);

	m_itemCount = 0;

	m_font.setSmooth(false);

	m_itemNameText.setCharacterSize(12U);
	m_itemNameText.setFillColor(sf::Color::White);
	m_itemNameText.setPosition(m_position);

	m_itemDescriptionText.setCharacterSize(8U);
	m_itemDescriptionText.setFillColor(sf::Color::White);
	m_itemDescriptionText.setPosition(m_position);

	m_textPosition = sf::Vector2f(m_position.x, m_position.y + 100.0f);

	m_hoveringItem = false;

}

Inventory::~Inventory()
{
}

void Inventory::update(sf::RenderWindow& t_window)
{
	sf::Vector2f mousePosition = t_window.mapPixelToCoords(sf::Mouse::getPosition(t_window));

	m_hoveringItem = false;

	for (Item& item : m_items)
	{
		if (item.sprite.getGlobalBounds().contains(mousePosition))
		{
			m_highlightPos = item.sprite.getPosition();
			m_highlightSprite.setPosition(m_highlightPos);

			m_itemNameText.setString(item.name);
			m_itemNameText.setOrigin(m_itemNameText.getLocalBounds().getCenter());
			m_itemDescriptionText.setString(item.description);
			m_itemDescriptionText.setOrigin(m_itemDescriptionText.getLocalBounds().getCenter());

			m_itemNameText.setPosition(m_textPosition);
			m_itemDescriptionText.setPosition(m_textPosition + sf::Vector2f(-30.0f, 50.0f));

			m_hoveringItem = true;
		}
	}
}

void Inventory::render(sf::RenderWindow& t_window, std::vector<sf::Sprite>& t_hearts)
{
	t_window.draw(m_inventoryBackground);
	t_window.draw(m_inventorySprite);

	for (Item& item : m_items)
	{
		t_window.draw(item.sprite);
	}

	float offset = 0.0f;
	for (sf::Sprite& heart : t_hearts)
	{
		heart.setPosition(sf::Vector2f(m_position.x - 312.0f + offset * 50.0f, m_position.y - 172.0f));
		offset++;

		t_window.draw(heart);
	}

	if (m_hoveringItem)
	{
		t_window.draw(m_itemNameText);
		t_window.draw(m_itemDescriptionText);
		t_window.draw(m_highlightSprite);
	}
}

void Inventory::addItem(sf::Texture* t_item)
{
	m_itemCount++;
	Item newItem(t_item);
	
	switch (m_itemCount)
	{
	case 1:
		newItem.name = "Potion of Speed";
		newItem.description = "Increases movement\nspeed";
		break;
	case 2:
		newItem.name = "Potion of Leaping";
		newItem.description = "Grants the ability\nto double jump.\n\n[W] key while falling\nto jump again";
		break;
	case 3:
		newItem.name = "Potion of Dashing";
		newItem.description = "Grants the ability\nto dash.\n\n[LShift] key\nto dash";
		break;
	default:
		break;
	}

	newItem.sprite.setOrigin(newItem.sprite.getGlobalBounds().getCenter());
	newItem.sprite.setScale(sf::Vector2f(3.0f, 3.0f));
	newItem.sprite.setPosition(m_itemStartPos + sf::Vector2f(m_items.size() * m_itemOffset, 0.0f));

	m_items.push_back(newItem);
}

void Inventory::centreOnScreen(sf::Vector2f t_viewPosition)
{
	m_position = t_viewPosition;
	m_inventoryBackground.setPosition(m_position);
	m_inventorySprite.setPosition(m_position);
	m_textPosition = sf::Vector2f(m_position.x + 38.0f, m_position.y - 134.0f);
	m_itemStartPos = sf::Vector2f(m_position.x - 44.0f, m_position.y + 56.0f);
	
	for (int i = 0; i < m_items.size(); i++)
	{
		if (i < 3)
		{
			m_items[i].sprite.setPosition(m_itemStartPos + sf::Vector2f(i * m_itemOffset, 0.0f));
		}
		else
		{
			m_items[i].sprite.setPosition(m_itemStartPos + sf::Vector2f((i - 3) * m_itemOffset, 74.0f));
		}
	}
}

int Inventory::getItemCount()
{
	return m_itemCount;
}
