#pragma once

#include <string>

#include <SFML\Graphics.hpp>

#include "SpriteSheetManager.h"

#include "AnimatedSprite.h"

class Tile
{
public:
	Tile(AnimatedSprite* s);
	~Tile(void);

	const AnimatedSprite* getSprite() const;
	AnimatedSprite* sprite; // as this class will contain more info, some sprites should be batched
private:
};

