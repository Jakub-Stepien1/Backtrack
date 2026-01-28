//Jakub Stepien

#include "Game.h"
#include <iostream>

/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the texts
/// load and setup the images
/// load and setup the sounds
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ sf::Vector2u{1368U, 768U}, 32U }, "Backtrack" }, // 1368x768 = 16:9 aspect ratio (38x21 tiles)
	m_currentGameState{ Gamestate::TitleScreen }
{
	setup(); // load all resources and game data
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	while (const std::optional newEvent = m_window.pollEvent())
	{
		if ( newEvent->is<sf::Event::Closed>()) // close window message 
		{
			m_window.close();
		}
		if (newEvent->is<sf::Event::KeyPressed>()) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(const std::optional<sf::Event> t_event)
{
	const sf::Event::KeyPressed *newKeypress = t_event->getIf<sf::Event::KeyPressed>();
	if (sf::Keyboard::Key::Escape == newKeypress->code)
	{
		m_currentGameState = Gamestate::Menu;
	}

	if (m_currentGameState == TitleScreen)
	{
		m_currentGameState = Gamestate::Menu;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	switch (m_currentGameState)	
	{
	case TitleScreen:
		updateTitleScreen(t_deltaTime);
		break;
	case Menu:
		updateMenu(t_deltaTime);
		break;
	case LevelEditor:
		updateLevelEditor(t_deltaTime);
		break;
	case Gameplay:
		updateGameplay(t_deltaTime);
		break;
	case Pause:
		break;
	case Dialogue:
		break;
	default:
		break;
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	switch (m_currentGameState)
	{
	case TitleScreen:
		renderTitleScreen();
		break;
	case Menu:
		renderMenu();
		break;
	case LevelEditor:
		renderLevelEditor();
		break;
	case Gameplay:
		renderGameplay();
		break;
	case Pause:
		break;
	case Dialogue:
		break;
	default:
		break;
	}
	
	m_window.display();
}

void Game::updateTitleScreen(sf::Time t_deltaTime)
{
	if (m_titleScreenText.getPosition().y > 703.0f)
	{
		m_textVel = sf::Vector2f(0.0f, -10.0f * t_deltaTime.asSeconds());
	}
	else if (m_titleScreenText.getPosition().y < 697.0f)
	{
		m_textVel = sf::Vector2f(0.0f, 10.0f * t_deltaTime.asSeconds());
	}
	m_titleScreenText.move(m_textVel);
	m_logoSprite.move(m_textVel);
}

void Game::updateMenu(sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	
	for (MenuButton& button : m_menuButtons)
	{
		if (button.isMouseOver(mousePosition))
		{
			button.hover();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				if (button.getText() == "Play")
				{
					for (int row = 0; row < TILE_ROWS; row++)
					{
						for (int col = 0; col < TILE_COLS; col++)
						{
							m_tiles[row][col].showOutline(false);
						}
					}

					m_currentGameState = Gamestate::Gameplay;
				}
				else if (button.getText() == "Level Editor")
				{
					for (int row = 0; row < TILE_ROWS; row++)
					{
						for (int col = 0; col < TILE_COLS; col++)
						{
							m_tiles[row][col].showOutline(true);
						}
					}

					m_currentGameState = Gamestate::LevelEditor;
				}
				else if (button.getText() == "Options")
				{
					// Open options menu
				}
				else if (button.getText() == "Exit")
				{
					m_window.close();
				}
			}
		}
		else
		{
			button.unhover();
		}
	}

	if (m_logoSprite.getPosition().y > 253.0f)
	{
		m_textVel = sf::Vector2f(0.0f, -10.0f * t_deltaTime.asSeconds());
	}
	else if (m_logoSprite.getPosition().y < 247.0f)
	{
		m_textVel = sf::Vector2f(0.0f, 10.0f * t_deltaTime.asSeconds());
	}

	m_logoSprite.move(m_textVel);
}

void Game::updateLevelEditor(sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		selectedTile = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		selectedTile = 2;
	}

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			if (m_tiles[row][col].isMouseOver(mousePosition))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_grid[row][col] = selectedTile;
					SurroundingTiles surrounding = getSurroundingTiles(row, col);
					m_tiles[row][col].setTile(selectedTile, surrounding);
				}
				else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
				{
					m_grid[row][col] = 0;
					SurroundingTiles surrounding = getSurroundingTiles(row, col);
					m_tiles[row][col].setTile(0, surrounding);
				}
			}

			if (m_grid[row][col] != 0)
			{
				SurroundingTiles surrounding = getSurroundingTiles(row, col);
				m_tiles[row][col].setTile(m_grid[row][col], surrounding);
			}
		}
	}
	
}

void Game::updateGameplay(sf::Time t_deltaTime)
{
	bool noTileCollision = true;

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			if (m_grid[row][col] != 0)
			{
				if (m_player.checkGroundCollision(m_tiles[row][col]))
				{
					m_player.calculateGroundLevel(m_tiles[row][col]);
					noTileCollision = false;
				}
			}
		}
	}

	if (noTileCollision)
	{
		m_player.setGroundLevel(2000.0f);
	}

	m_player.update();
}

void Game::renderTitleScreen()
{
	m_window.draw(m_titleScreenSprite);
	m_window.draw(m_logoSprite);
	m_window.draw(m_titleScreenText);
}

void Game::renderMenu()
{
	m_window.draw(m_menuBackgroundSprite);
	m_window.draw(m_logoSprite);

	for (MenuButton& button : m_menuButtons)
	{
		button.render(m_window);
	}
}

void Game::renderLevelEditor()
{
	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			m_tiles[row][col].render(m_window);
		}
	}
}

void Game::renderGameplay()
{
	//m_window.draw(m_backgroundSprite);

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			if (m_grid[row][col] != 0)
			{
				m_tiles[row][col].render(m_window);
			}
		}
	}

	m_player.render(m_window);
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setup()
{
	setupImages(); // load images
	setupFonts();  // load fonts
	setupSounds(); // load sounds

	setupMenu(); // setup menu objects
	setupGameplay(); // setup game objects

}

void Game::setupImages()
{
	if (!m_titleScreenTexture.loadFromFile("ASSETS\\IMAGES\\background-title.png"))
	{
		std::cout << "problem loading title screen background" << std::endl;
	}
	m_titleScreenSprite.setTexture(m_titleScreenTexture, true);
	m_titleScreenSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\logo-title.png"))
	{
		std::cout << "problem loading menu logo image" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture, true);
	m_logoSprite.setScale(sf::Vector2f(0.5f, 0.5f));
	m_logoSprite.setPosition(sf::Vector2f(500.0f, 250.0f));
	m_logoSprite.setOrigin(m_logoSprite.getGlobalBounds().getCenter());

	if (!m_menuBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\background-menu.png"))
	{
		std::cout << "problem loading menu background" << std::endl;
	}
	m_menuBackgroundSprite.setTexture(m_menuBackgroundTexture, true);

	if (!m_tileSetTexture.loadFromFile("ASSETS\\IMAGES\\terrain18px-sheet.png"))
	{
		std::cout << "problem loading tileset" << std::endl;
	}

	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading background" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture, true);
	m_backgroundSprite.setScale(sf::Vector2f(1.2f, 1.6f));
}

void Game::setupFonts()
{
	if (!m_backtrackFont.openFromFile("ASSETS\\FONTS\\Backtrack-Regular-font.ttf"))
	{
		std::cout << "problem loading backtrack font" << std::endl;
	}
	m_titleScreenText.setFont(m_backtrackFont);
	m_titleScreenText.setCharacterSize(48U);
	m_titleScreenText.setString("Press any key to start!");
	m_titleScreenText.setOrigin(m_titleScreenText.getLocalBounds().getCenter());
	m_titleScreenText.setPosition(sf::Vector2f{ 684.0f, 700.0f });
	m_titleScreenText.setOutlineColor(sf::Color::White);
	m_titleScreenText.setOutlineThickness(0.7f);
	m_titleScreenText.setFillColor(sf::Color::White);

	m_textVel = sf::Vector2f(0.0f, 3.0f);
}

void Game::setupSounds()
{
	if (!m_DELETEsoundBuffer.loadFromFile("ASSETS\\AUDIO\\beep.wav"))
	{
		std::cout << "Error loading beep sound" << std::endl;
	}
	//m_DELETEsound.play(); // test sound
}

void Game::setupMenu()
{
	selectedTile = 0;

	for (int i = 0; i < 4; i++)
	{
		MenuButton newButton;
		newButton.setFont(m_backtrackFont);
		newButton.setPosition(sf::Vector2f(200.0f, 400.0f + 80 * i ));
		if (i == 0)
		{
			newButton.setText("Play");
		}
		else if (i == 1)
		{
			newButton.setText("Level Editor");
		}
		else if (i == 2)
		{
			newButton.setText("Options");
		}
		else if (i == 3)
		{
			newButton.setText("Exit");
		}

		m_menuButtons.push_back(newButton);
	}
}

void Game::setupGameplay()
{
	loadLevel(1);

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			SurroundingTiles surrounding{ 0,0,0,0,0,0,0,0 };
			surrounding = getSurroundingTiles(row, col);

			m_tiles[row][col].setTile(m_grid[row][col], surrounding);
			m_tiles[row][col].setPosition(sf::Vector2f((col - 1) * 18 * TILE_SCALE, (row - 1) * 18 * TILE_SCALE)); // offset by one tile to account for offscreen tiles
			m_tiles[row][col].setTexture(m_tileSetTexture);
		}
	}
}

SurroundingTiles Game::getSurroundingTiles(int t_row, int t_col)
{
	SurroundingTiles surrounding{ 0,0,0,0,0,0,0,0 };
	int col = t_col;
	int row = t_row;

	if (col > 0)
	{
		surrounding.left = m_grid[row][col - 1];
	}
	if (col < TILE_COLS - 1)
	{
		surrounding.right = m_grid[row][col + 1];
	}
	if (row > 0)
	{
		surrounding.top = m_grid[row - 1][col];
	}
	if (row < TILE_ROWS - 1)
	{
		surrounding.bottom = m_grid[row + 1][col];
	}
	if (col > 0 && row > 0)
	{
		surrounding.topLeft = m_grid[row - 1][col - 1];
	}
	if (col < TILE_COLS - 1 && row > 0)
	{
		surrounding.topRight = m_grid[row - 1][col + 1];
	}
	if (col > 0 && row < TILE_ROWS - 1)
	{
		surrounding.bottomLeft = m_grid[row + 1][col - 1];
	}
	if (col < TILE_COLS - 1 && row < TILE_ROWS - 1)
	{
		surrounding.bottomRight = m_grid[row + 1][col + 1];
	}

	return surrounding;
}

void Game::loadLevel(int t_level)
{
	std::ifstream file("ASSETS\\LEVELS\\level" + std::to_string(t_level) + ".txt");

	if (!file.is_open())
	{
		std::cout << "Error opening level file: ASSETS\\LEVELS\\level" + std::to_string(t_level) + ".txt" << std::endl;
		return;
	}

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			file >> m_grid[row][col];
		}
	}
}
