#pragma once

#include <string>
#include <map>

#include <SFML\Graphics.hpp>

#include "SpriteSheet.h"
#include "TileGame.h"

class SpriteSheetManager
{
public:

	static SpriteSheetManager* initialize();
	static SpriteSheetManager* instance();

	~SpriteSheetManager(void);

	// maybe add a release ? (so an unload in private)
	SpriteSheet* retrieve(const std::string& textureName);

	// this gets the sprite linking 4 game tiles
	sf::Sprite* getTile(TileGame::tileType upLeft, TileGame::tileType leftDown, TileGame::tileType downRight, TileGame::tileType rightUp);

private:
	// map of sprites corresponding to linkers of gametiles :
	// tiles[upLeft][leftDown][downRight][rightUp]
	sf::Sprite* tiles[TileGame::NUMBER_OF_TILES_TYPE][TileGame::NUMBER_OF_TILES_TYPE][TileGame::NUMBER_OF_TILES_TYPE][TileGame::NUMBER_OF_TILES_TYPE];
	std::map< std::string, SpriteSheet*> textures;
	
	SpriteSheetManager(void);

	SpriteSheet* load(const std::string& textureName);
};

