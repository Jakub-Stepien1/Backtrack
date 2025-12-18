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
	m_DELETEexitGame{false} //when true game will exit
{
	setup(); // load font and sounds
	setupImages(); // load images
	setupGame(); // setup game objects
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
			m_DELETEexitGame = true;
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
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Check if any keys are currently pressed
/// </summary>
void Game::checkKeyboardState()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		m_DELETEexitGame = true; 
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	checkKeyboardState();
	if (m_DELETEexitGame)
	{
		m_window.close();
	}

	bool noPlatformCollision = true;

	for (Platform& platform : m_platforms)
	{
		platform.activateInRange(m_player.getPosition());

		if (platform.isActive() && m_player.checkGroundCollision(platform))
		{
			m_player.calculateGroundLevel(platform);
			noPlatformCollision = false;
		}
	}

	if (noPlatformCollision)
	{
		m_player.setGroundLevel(2000.0f);
	}

	m_player.update();

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);

	//m_window.draw(m_backgroundSprite);

	for (Platform& platform : m_platforms)
	{
		if (platform.isActive())
		{
			platform.render(m_window);
		}
	}

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

	//m_window.draw(m_DELETElogoSprite);
	//m_window.draw(m_DELETEwelcomeMessage);
	
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setup()
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

	if (!m_DELETEsoundBuffer.loadFromFile("ASSETS\\AUDIO\\beep.wav"))
	{
		std::cout << "Error loading beep sound" << std::endl;
	}
	//m_DELETEsound.play(); // test sound

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

void Game::setupGame()
{
	Platform ground;
	m_platforms.push_back(ground);

	Platform platform1(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(600.0f, 500.0f));
	m_platforms.push_back(platform1);

	Platform platform2(sf::Vector2f(200.0f, 20.0f), sf::Vector2f(400.0f, 400.0f));
	m_platforms.push_back(platform2);

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
