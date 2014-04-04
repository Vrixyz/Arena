#include "SpriteSheet.h"


SpriteSheet::SpriteSheet(sf::Texture& texture): t(texture)
{

}


SpriteSheet::~SpriteSheet(void)
{
}

Animation* SpriteSheet::getAnimation(const std::string& name)
{
	return animations[name];
}

void SpriteSheet::addAnimation(const std::string& s, Animation* animation)
{
	animations[s] = animation;
}