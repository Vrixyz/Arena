#pragma once

class TileGame
{
public:
	typedef enum {
		Unknown = 0, // explicit because will be in a table
		Grass = 1,
		Earth = 2,
		NUMBER_OF_TILES_TYPE = 3 // that's why it should be explicit too !
	} tileType;
	tileType type;
	TileGame(tileType);
	~TileGame(void);
};

