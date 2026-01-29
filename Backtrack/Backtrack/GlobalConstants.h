#pragma once
#include <SFML/Graphics.hpp>

const sf::Vector2i TILE_SIZE{ 18, 18 };
static const int TILE_SCALE = 2;

static const sf::Vector2f BACKGROUND_SCALE = sf::Vector2f(3.0f, 4.0f);

static const int TILE_ROWS = 23; // 21 + 2 offscreen (1 on each side)
static const int TILE_COLS = 40; // 38 + 2 offscreen (1 on each side)

///////////////////////////////////////////////// Tile texture rectangles /////////////////////////////////////////////////

// Grass Tiles
const sf::IntRect GRASS_TOP_LEFT{ sf::Vector2i(0, 54), TILE_SIZE };
const sf::IntRect GRASS_TOP_MIDDLE{ sf::Vector2i(18, 54), TILE_SIZE };
const sf::IntRect GRASS_TOP_RIGHT{ sf::Vector2i(36, 54), TILE_SIZE };

const sf::IntRect GRASS_MIDDLE_LEFT{ sf::Vector2i(0, 72), TILE_SIZE };
const sf::IntRect GRASS_MIDDLE_MIDDLE{ sf::Vector2i(18, 72), TILE_SIZE };
const sf::IntRect GRASS_MIDDLE_RIGHT{ sf::Vector2i(36, 72), TILE_SIZE };

const sf::IntRect GRASS_BOTTOM_LEFT{ sf::Vector2i(0, 90), TILE_SIZE };
const sf::IntRect GRASS_BOTTOM_MIDDLE{ sf::Vector2i(18, 90), TILE_SIZE };
const sf::IntRect GRASS_BOTTOM_RIGHT{ sf::Vector2i(36, 90), TILE_SIZE };

const sf::IntRect GRASS_CORNER_BOTTOM_LEFT{ sf::Vector2i(54, 36), TILE_SIZE };
const sf::IntRect GRASS_CORNER_BOTTOM_RIGHT{ sf::Vector2i(72, 36), TILE_SIZE };
const sf::IntRect GRASS_CORNER_TOP_LEFT{ sf::Vector2i(54, 54), TILE_SIZE };
const sf::IntRect GRASS_CORNER_TOP_RIGHT{ sf::Vector2i(72, 54), TILE_SIZE };

const sf::IntRect GRASS_DIAGONAL_LEFT{ sf::Vector2i(72, 90), TILE_SIZE };
const sf::IntRect GRASS_DIAGONAL_RIGHT{ sf::Vector2i(54, 90), TILE_SIZE };

// Brick Tiles
const sf::IntRect BRICK_TOP_LEFT{ sf::Vector2i(0, 0), TILE_SIZE };
const sf::IntRect BRICK_TOP_MIDDLE{ sf::Vector2i(18, 0), TILE_SIZE };
const sf::IntRect BRICK_TOP_RIGHT{ sf::Vector2i(36, 0), TILE_SIZE };

const sf::IntRect BRICK_MIDDLE_LEFT{ sf::Vector2i(0, 18), TILE_SIZE };
const sf::IntRect BRICK_MIDDLE_MIDDLE{ sf::Vector2i(18, 18), TILE_SIZE };
const sf::IntRect BRICK_MIDDLE_RIGHT{ sf::Vector2i(36, 18), TILE_SIZE };

const sf::IntRect BRICK_BOTTOM_LEFT{ sf::Vector2i(0, 36), TILE_SIZE };
const sf::IntRect BRICK_BOTTOM_MIDDLE{ sf::Vector2i(18, 36), TILE_SIZE };
const sf::IntRect BRICK_BOTTOM_RIGHT{ sf::Vector2i(36, 36), TILE_SIZE };

const sf::IntRect BRICK_CORNER_BOTTOM_LEFT{ sf::Vector2i(54, 0), TILE_SIZE };
const sf::IntRect BRICK_CORNER_BOTTOM_RIGHT{ sf::Vector2i(72, 0), TILE_SIZE };
const sf::IntRect BRICK_CORNER_TOP_LEFT{ sf::Vector2i(54, 18), TILE_SIZE };
const sf::IntRect BRICK_CORNER_TOP_RIGHT{ sf::Vector2i(72, 18), TILE_SIZE };

//const sf::IntRect BRICK_DIAGONAL_LEFT{ sf::Vector2i(72, 90), TILE_SIZE }; // no sprite yet
//const sf::IntRect BRICK_DIAGONAL_RIGHT{ sf::Vector2i(54, 90), TILE_SIZE }; // no sprite yet