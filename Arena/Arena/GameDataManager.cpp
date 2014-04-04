#include "GameDataManager.h"


GameDataManager::GameDataManager(void)
{
}


GameDataManager::~GameDataManager(void)
{
}

GameUpdater::TileMap*	GameDataManager::getKnownTiles() const
{
	return server.buildKnownTiles(5);
}

sf::Vector2f GameDataManager::getPlayerposition() const
{
	return sf::Vector2f(server.getPlayerPosition()[0], server.getPlayerPosition()[1]);
}

void GameDataManager::update(float seconds)
{
	server.update(seconds);
}