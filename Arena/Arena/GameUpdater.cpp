#include "GameUpdater.h"

float GameUpdater::playerMaxSpeed = 3;

GameUpdater::GameUpdater(void)
{
	playerPosition[0] = 0;
	playerPosition[1] = 0;
	relativeAim[0] = 0;
	relativeAim[1] = 0;
	playerSpeed[0] = 0;
	playerSpeed[1] = 0;
}


GameUpdater::~GameUpdater(void)
{
}

const float* GameUpdater::getPlayerPosition() const
{
	return playerPosition;
}

void GameUpdater::movePlayerUp()
{
	playerSpeed[1] = playerMaxSpeed;
}

void GameUpdater::movePlayerLeft()
{
	playerSpeed[0] = -playerMaxSpeed;
}

void GameUpdater::movePlayerDown(){
	playerSpeed[1] = -playerMaxSpeed;
}

void GameUpdater::movePlayerRight()
{
	playerSpeed[0] = playerMaxSpeed;
}

void GameUpdater::setRelativeAimPoint(float x, float y)
{
	relativeAim[0] = x;
	relativeAim[1] = y;
}

void GameUpdater::update(float seconds)
{
	playerPosition[0] += playerSpeed[0] * seconds;
	playerPosition[1] += playerSpeed[1] * seconds;
	playerSpeed[0] = 0;
	playerSpeed[1] = 0;
}

GameUpdater::TileMap*	GameUpdater::buildKnownTiles(int viewRange) const
{
	TileMap* map = new TileMap();

	return rec_buildKnownTiles(map, viewRange + 1, (int)Utils::round(playerPosition[0]), (int)Utils::round(playerPosition[1]));
}

GameUpdater::TileMap*	GameUpdater::rec_buildKnownTiles(TileMap* m, int viewRange, int x, int y) const
{
	if (viewRange < 0)
		return m;
	if (!m->count(x))
	{
		(*m)[x] = new tileColumn();
	}
	else if (!(*m)[x]->count(y)) // case not filled yet
	{
		if (gameTiles.count(x))
			(*(*m)[x])[y] = (*gameTiles.at(x))[y];
	}
	rec_buildKnownTiles(m, viewRange - 1, x, y + 1);
	rec_buildKnownTiles(m, viewRange - 1, x - 1, y);
	rec_buildKnownTiles(m, viewRange - 1, x, y - 1);
	rec_buildKnownTiles(m, viewRange - 1, x + 1, y);
	return m;
}