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
	m_currentGameState{ Gamestate::Menu }
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
		m_window.close();
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_window.close();
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();

	switch (m_currentGameState)	
	{
	case Menu:
		updateMenu(t_deltaTime);
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

	//m_window.draw(m_backgroundSprite);

	switch (m_currentGameState)
	{
	case Menu:
		renderMenu();
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

void Game::updateMenu(sf::Time t_deltaTime)
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	
	if (m_playButton.isMouseOver(mousePosition))
	{
		m_playButton.hover();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_currentGameState = Gamestate::Gameplay;
		}
	}
	else
	{
		m_playButton.unhover();
	}

	if (m_optionsButton.isMouseOver(mousePosition))
	{
		m_optionsButton.hover();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			// Open options menu
		}
	}
	else
	{
		m_optionsButton.unhover();
	}

	if (m_exitButton.isMouseOver(mousePosition))
	{
		m_exitButton.hover();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			m_window.close();
		}
	}
	else
	{
		m_exitButton.unhover();
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

void Game::renderMenu()
{
	m_playButton.render(m_window);
	m_optionsButton.render(m_window);
	m_exitButton.render(m_window);
}

void Game::renderGameplay()
{
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
	if (!m_backgroundTexture.loadFromFile("ASSETS\\IMAGES\\background.png"))
	{
		std::cout << "problem loading background" << std::endl;
	}
	m_backgroundSprite.setTexture(m_backgroundTexture, true);
	m_backgroundSprite.setScale(sf::Vector2f(1.2f, 1.6f));

	if (!m_tileSetTexture.loadFromFile("ASSETS\\IMAGES\\terrain18px-sheet.png"))
	{
		std::cout << "problem loading tileset" << std::endl;
	}
}

void Game::setupFonts()
{
	if (!m_jerseyFont.openFromFile("ASSETS\\FONTS\\Jersey20-Regular.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_DELETEwelcomeMessage.setFont(m_jerseyFont);
	m_DELETEwelcomeMessage.setString("SFML Game");
	m_DELETEwelcomeMessage.setPosition(sf::Vector2f{ 205.0f, 240.0f });
	m_DELETEwelcomeMessage.setCharacterSize(96U);
	m_DELETEwelcomeMessage.setOutlineColor(sf::Color::Black);
	m_DELETEwelcomeMessage.setFillColor(sf::Color::Red);
	m_DELETEwelcomeMessage.setOutlineThickness(2.0f);
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
	m_playButton.setFont(m_jerseyFont);
	m_playButton.setPosition(sf::Vector2f(684.0f, 250.0f));
	m_playButton.setText("Play");

	m_optionsButton.setFont(m_jerseyFont);
	m_optionsButton.setPosition(sf::Vector2f(684.0f, 400.0f));
	m_optionsButton.setText("Options");

	m_exitButton.setFont(m_jerseyFont);
	m_exitButton.setPosition(sf::Vector2f(684.0f, 550.0f));
	m_exitButton.setText("Exit");
}

void Game::setupGameplay()
{
	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			SurroundingTiles surrounding{ 0,0,0,0,0,0,0,0 };
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

			m_tiles[row][col].setTile(m_grid[row][col], surrounding);
			m_tiles[row][col].setPosition(sf::Vector2f(col * 18 * TILE_SCALE, row * 18 * TILE_SCALE));
			m_tiles[row][col].setTexture(m_tileSetTexture);
		}
	}
}
