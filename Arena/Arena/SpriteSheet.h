#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <list>

#include "AnimatedSprite.h"

class SpriteSheet
{
public:
	SpriteSheet(sf::Texture& t);
	~SpriteSheet(void);
	
	void addAnimation(const std::string&, Animation*);
	Animation* getAnimation(const std::string& name);// not const, so we can get a same animated sprite (batched) (careful with use though, better to copy that)
	sf::Texture& t; // already stored in animation...
private:
	std::map<std::string, Animation* > animations;
};

