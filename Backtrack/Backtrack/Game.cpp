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
	m_window{ sf::VideoMode{ sf::Vector2u{1368U, 768U}, 64U }, "Backtrack" }, // 1368x768 = 16:9 aspect ratio (38x21 tiles)
	m_currentGameState{ Gamestate::TitleScreen },
	m_defaultView{sf::FloatRect( sf::Vector2f(0, 0), sf::Vector2f(m_window.getSize().x, m_window.getSize().y)) },
	m_playerView{ sf::FloatRect(sf::Vector2f(0, 0), sf::Vector2f(m_window.getSize().x / 1.2f, m_window.getSize().y) / 1.2f) }
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
		if (newEvent->is<sf::Event::MouseButtonPressed>())
		{
			if (m_currentGameState == TitleScreen)
			{
				changeGameState(Gamestate::Menu);
			}
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
		changeGameState(Gamestate::Menu);
	}

	if (m_currentGameState == TitleScreen)
	{
		changeGameState(Gamestate::Menu);
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

	m_titleScreenParticlesSprite.move(m_textVel);
	m_titleScreenCatSprite.move(-m_textVel);

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
					changeGameState(Gamestate::Gameplay);
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
					changeGameState(Gamestate::LevelEditor);
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
	bool noGroundCollision = true;

	handleCameraMovement(t_deltaTime);
	parallaxBackground(t_deltaTime);

	for (int row = 0; row < TILE_ROWS; row++)
	{
		for (int col = 0; col < TILE_COLS; col++)
		{
			if (m_grid[row][col] != 0
				&& m_tiles[row][col].distanceToTile(m_player.getPosition()) < 150)
			{
				m_player.checkCeilingCollisions(m_tiles[row][col]);
				m_player.checkSideCollisions(m_tiles[row][col]);

				if (m_player.checkGroundCollisions(m_tiles[row][col]))
				{
					noGroundCollision = false;
				}
			}
		}
	}

	if (noGroundCollision)
	{
		m_player.setGroundLevel(2000.0f);
	}

	m_player.update();
}

void Game::renderTitleScreen()
{
	m_window.draw(m_titleScreenBackgroundSprite);
	m_window.draw(m_logoSprite);
	m_window.draw(m_titleScreenParticlesSprite);
	m_window.draw(m_titleScreenCatSprite);

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
	m_window.draw(m_background1Sprite);
	m_window.draw(m_background2Sprite);
	m_window.draw(m_background3Sprite);
	m_window.draw(m_background4Sprite);
	m_window.draw(m_background5Sprite);

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
	if (!m_titleScreenBackgroundTexture.loadFromFile("ASSETS\\IMAGES\\title-background.png"))
	{
		std::cout << "problem loading title screen background" << std::endl;
	}
	m_titleScreenBackgroundSprite.setTexture(m_titleScreenBackgroundTexture, true);
	m_titleScreenBackgroundSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	if (!m_titleScreenParticlesTexture.loadFromFile("ASSETS\\IMAGES\\title-sparkle.png"))
	{
		std::cout << "problem loading title screen particles" << std::endl;
	}
	m_titleScreenParticlesSprite.setTexture(m_titleScreenParticlesTexture, true);
	m_titleScreenParticlesSprite.setScale(sf::Vector2f(0.5f, 0.5f));

	if (!m_titleScreenCatTexture.loadFromFile("ASSETS\\IMAGES\\title-cat.png"))
	{
		std::cout << "problem loading title screen cat" << std::endl;
	}
	m_titleScreenCatSprite.setTexture(m_titleScreenCatTexture, true);
	m_titleScreenCatSprite.setScale(sf::Vector2f(0.5f, 0.5f));

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

	if (!m_background1Texture.loadFromFile("ASSETS\\IMAGES\\skybox1.png"))
	{
		std::cout << "problem loading background layer 1" << std::endl;
	}
	m_background1Sprite.setTexture(m_background1Texture, true);
	m_background1Sprite.setOrigin(m_background1Sprite.getGlobalBounds().getCenter());
	m_background1Sprite.setScale(BACKGROUND_SCALE);
	m_background1Sprite.setPosition(m_defaultView.getCenter());
	
	if (!m_background2Texture.loadFromFile("ASSETS\\IMAGES\\skybox2.png"))
	{
		std::cout << "problem loading background layer 2" << std::endl;
	}
	m_background2Sprite.setTexture(m_background2Texture, true);
	m_background2Sprite.setOrigin(m_background2Sprite.getGlobalBounds().getCenter());
	m_background2Sprite.setScale(BACKGROUND_SCALE);
	m_background2Sprite.setPosition(m_defaultView.getCenter());
	
	if (!m_background3Texture.loadFromFile("ASSETS\\IMAGES\\skybox3.png"))
	{
		std::cout << "problem loading background layer 3" << std::endl;
	}
	m_background3Sprite.setTexture(m_background3Texture, true);
	m_background3Sprite.setOrigin(m_background3Sprite.getGlobalBounds().getCenter());
	m_background3Sprite.setScale(BACKGROUND_SCALE);
	m_background3Sprite.setPosition(m_defaultView.getCenter());

	if (!m_background4Texture.loadFromFile("ASSETS\\IMAGES\\skybox4.png"))
	{
		std::cout << "problem loading background layer 4" << std::endl;
	}
	m_background4Sprite.setTexture(m_background4Texture, true);
	m_background4Sprite.setOrigin(m_background4Sprite.getGlobalBounds().getCenter());
	m_background4Sprite.setScale(BACKGROUND_SCALE);
	m_background4Sprite.setPosition(m_defaultView.getCenter());

	if (!m_background5Texture.loadFromFile("ASSETS\\IMAGES\\skybox5.png"))
	{
		std::cout << "problem loading background layer 5" << std::endl;
	}
	m_background5Sprite.setTexture(m_background5Texture, true);
	m_background5Sprite.setOrigin(m_background5Sprite.getGlobalBounds().getCenter());
	m_background5Sprite.setScale(BACKGROUND_SCALE);
	m_background5Sprite.setPosition(m_defaultView.getCenter());
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

void Game::changeGameState(Gamestate t_newState)
{
	switch (t_newState)
	{
	case TitleScreen:
		m_window.setView(m_defaultView);
		m_currentGameState = TitleScreen;
		break;
	case Menu:
		m_window.setView(m_defaultView);
		m_currentGameState = Menu;
		break;
	case LevelEditor:
		m_window.setView(m_defaultView);
		m_currentGameState = LevelEditor;
		break;
	case Gameplay:
		m_window.setView(m_playerView);
		m_currentGameState = Gameplay;
		break;
	case Pause:
		m_currentGameState = Pause;
		break;
	case Dialogue:
		m_currentGameState = Dialogue;
		break;
	default:
		break;
	}
}

void Game::handleCameraMovement(sf::Time t_deltaTime)
{
	sf::Vector2f currentViewPos = m_playerView.getCenter();
	sf::Vector2f targetViewPos = m_player.getPosition();

	float cameraSpeed = t_deltaTime.asSeconds() * 10.0f;

	currentViewPos = currentViewPos + (targetViewPos - currentViewPos) * cameraSpeed;

	if (currentViewPos.x < m_playerView.getSize().x / 2.0f )
	{
		currentViewPos.x = m_playerView.getSize().x / 2.0f;
	}
	else if (currentViewPos.x > m_defaultView.getSize().x - m_playerView.getSize().x / 2.0f)
	{
		currentViewPos.x = m_defaultView.getSize().x - m_playerView.getSize().x / 2.0f;
	}
	if (currentViewPos.y < m_playerView.getSize().y / 2.0f)
	{
		currentViewPos.y = m_playerView.getSize().y / 2.0f;
	}
	else if (currentViewPos.y > m_defaultView.getSize().y - m_playerView.getSize().y / 2.0f)
	{
		currentViewPos.y = m_defaultView.getSize().y - m_playerView.getSize().y / 2.0f;
	}

	m_playerView.setCenter(currentViewPos);
	m_window.setView(m_playerView);
}

void Game::parallaxBackground(sf::Time t_deltaTime)
{
	sf::Vector2f viewCenter = m_playerView.getCenter();
	sf::Vector2f defaultCenter = m_defaultView.getCenter();

	for (int i = 0; i < 5; i++)
	{
		float parallaxSpeed = t_deltaTime.asSeconds() * (5.0f + i * 4.0f);
		sf::Vector2f backgroundPos = defaultCenter + (viewCenter - defaultCenter) * parallaxSpeed;

		switch (i)
		{
		case 0:
			m_background5Sprite.setPosition(backgroundPos);
			break;
		case 1:
			m_background4Sprite.setPosition(backgroundPos);
			break;
		case 2:
			m_background3Sprite.setPosition(backgroundPos);
			break;
		case 3:
			m_background2Sprite.setPosition(backgroundPos);
			break;
		case 4:
			m_background1Sprite.setPosition(backgroundPos);
			break;
		default:
			break;
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
