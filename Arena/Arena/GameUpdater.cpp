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

#include <iostream>

GameUpdater::TileMap* GameUpdater::fillLine(int x1, int y1, int x2, int y2, GameUpdater::TileMap* map) const
{


	if (std::abs(x2 - x1) > std::abs(y2 - y1))
	{
		if(x2 < x1) { //switch x2 and x1
			x2^=x1;
			x1^=x2;
			x2^=x1;

			y2^=y1;
			y1^=y2;
			y2^=y1;
		}
		//if (x2 - x1 != 0)
		for(int x=x1; x<=x2; x++) //we follow x coord. one-by-one
		{
			int y=y1+(((float)(y2-y1)/(float)(x2-x1))*(x-x1)); //y is the same precentage of trip x made on its trip
			if (!map->count(x))
			{
				(*map)[x] = new GameUpdater::tileColumn();
			}
			else if (!(*map)[x]->count(y)) // case not filled yet
			{
				if (gameTiles.count(x))
				(*(*map)[x])[y] = (*gameTiles.at(x))[y];
			}
			//std::cout << x << ";" << y << " ";
		}
	}
	else
	{
		if(y2 < y1) { //switch x2 and x1
			x2^=x1;
			x1^=x2;
			x2^=x1;

			y2^=y1;
			y1^=y2;
			y2^=y1;
		}
		int x,y;
		if (y2-y1 != 0)
		for(y=y1; y<=y2; y++) //we follow y coord. one-by-one
		{
			x=x1+(((float)(x2-x1)/(float)(y2-y1))*(y-y1)); //x is the same percentage of trip y made on its trip
					if (!map->count(x))
			{
				(*map)[x] = new GameUpdater::tileColumn();
			}
			else if (!(*map)[x]->count(y)) // case not filled yet
			{
				if (gameTiles.count(x))
				(*(*map)[x])[y] = (*gameTiles.at(x))[y];
			}
			//std::cout << x << ";" << y << " ";
		}
	}
	//std::cout << std::endl;
	return map;
}

GameUpdater::TileMap*	GameUpdater::buildKnownTiles(int viewRange) const
{
	TileMap* map = new TileMap();
	float angle = std::atan2(relativeAim[0] , relativeAim[1]);
	angle  *= (float)(180 / M_PI);
	std::cout << " angle: " << angle << std::endl;

			int targetX = Utils::round(playerPosition[0] + relativeAim[0]);
			int targetY = Utils::round(playerPosition[1] + relativeAim[1]);
			std::cout << targetX << ";" << targetY << std::endl;
			int x1 = Utils::round(playerPosition[0]);
			int y1 = Utils::round(playerPosition[1]);
			map = fillLine(x1, y1, targetX, targetY, map);
map = fillLine(x1, y1, targetX, targetY + 1, map);
map = fillLine(x1, y1, targetX, targetY + 2, map);
map = fillLine(x1, y1, targetX, targetY + 3, map);
map = fillLine(x1, y1, targetX, targetY + 4, map);
map = fillLine(x1, y1, targetX, targetY - 1, map);
map = fillLine(x1, y1, targetX, targetY - 2, map);
map = fillLine(x1, y1, targetX, targetY - 3, map);
//map = fillLine(x1, y1, targetX, targetY - 4, map);

map = fillLine(x1, y1, targetX+1, targetY, map);
map = fillLine(x1, y1, targetX+2, targetY, map);
map = fillLine(x1, y1, targetX+3, targetY, map);
map = fillLine(x1, y1, targetX+4, targetY, map);
map = fillLine(x1, y1, targetX-1, targetY, map);
map = fillLine(x1, y1, targetX-2, targetY, map);
map = fillLine(x1, y1, targetX-3, targetY, map);
//map = fillLine(x1, y1, targetX-4, targetY, map);

map = fillLine(x1, y1, targetX + 1, targetY + 1, map);
map = fillLine(x1, y1, targetX + 2, targetY + 2, map);
map = fillLine(x1, y1, targetX + 3, targetY + 3, map);
map = fillLine(x1, y1, targetX - 1, targetY - 1, map);
map = fillLine(x1, y1, targetX - 2, targetY - 2, map);
//map = fillLine(x1, y1, targetX - 3, targetY - 3, map);
	return map;
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