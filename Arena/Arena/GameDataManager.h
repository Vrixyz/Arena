#pragma once

#include <map>
#include <SFML\Graphics.hpp>

#include "Tile.h"
#include "GameUpdater.h"

class GameDataManager
{
public:
	GameDataManager(void);
	~GameDataManager(void);
	GameUpdater::TileMap*	getKnownTiles() const;
	sf::Vector2f getPlayerposition() const;
	void update(float seconds);
	GameUpdater server;

	GameUpdater::TileMap knownTiles;
};

