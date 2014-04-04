#include "Tile.h"


Tile::Tile(AnimatedSprite* s) : sprite(s)
{
}


Tile::~Tile(void)
{
}

const AnimatedSprite* Tile::getSprite() const
{
	return sprite;
}