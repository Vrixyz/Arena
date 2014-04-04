#pragma once

#include <vector>
#include <map>
#include "Utils.h"
#include "TileGame.h"

class GameUpdater
{
public:
	typedef std::map<int, TileGame*> tileColumn;
	typedef std::map<int, tileColumn* > TileMap; // en faire une classe
	
	GameUpdater(void);
	~GameUpdater(void);
	const float* getPlayerPosition() const; // returns a ptr array[2]
	
	void movePlayerUp();
	void movePlayerLeft();
	void movePlayerDown();
	void movePlayerRight();
	void setRelativeAimPoint(float x, float y);


	void update(float seconds);
	TileMap*	buildKnownTiles(int viewRange) const;

	float playerSpeed[2];
	GameUpdater::TileMap gameTiles;
private:
	float playerPosition[2];
	float relativeAim[2];
	static float playerMaxSpeed;

	TileMap*	rec_buildKnownTiles(TileMap* m, int viewRange, int x, int y) const;


};

