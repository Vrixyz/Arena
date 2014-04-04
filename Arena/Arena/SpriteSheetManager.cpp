#include "SpriteSheetManager.h"

static SpriteSheetManager* _instance;

SpriteSheetManager* SpriteSheetManager::initialize()
{
	_instance = new SpriteSheetManager();
	return _instance;
}

SpriteSheetManager* SpriteSheetManager::instance()
{
	return _instance;
}


SpriteSheetManager::~SpriteSheetManager(void)
{
}

SpriteSheet* SpriteSheetManager::retrieve(const std::string& textureName)
{
	SpriteSheet* t = textures[textureName];
	if (t == NULL)
		t = this->load(textureName);
	return t;
}

#include <iostream>

sf::Sprite* SpriteSheetManager::getTile(TileGame::tileType upLeft, TileGame::tileType leftDown, TileGame::tileType downRight, TileGame::tileType rightUp)
{
	//if (tiles[upLeft][leftDown][downRight][rightUp])
		//std::cout <<  upLeft << leftDown << downRight << rightUp << std::endl;
	//return tiles[TileGame::Grass][TileGame::Grass][TileGame::Grass][TileGame::Grass];
	return tiles[upLeft][leftDown][downRight][rightUp];
}

SpriteSheetManager::SpriteSheetManager(void)
{
	for ( int i = 0; i < TileGame::NUMBER_OF_TILES_TYPE; ++i)
		for ( int j = 0; j < TileGame::NUMBER_OF_TILES_TYPE; ++j)
			for ( int k = 0; k < TileGame::NUMBER_OF_TILES_TYPE; ++k)
				for ( int l = 0; l < TileGame::NUMBER_OF_TILES_TYPE; ++l)
					tiles[i][j][k][l] = NULL;
}
// TODO: find a cleaner way that this massive mess ?
SpriteSheet* SpriteSheetManager::load(const std::string& textureName)
{
	sf::Texture* t = new sf::Texture();
	if (!t->loadFromFile(textureName))
	{
		// BAD!
	}

	SpriteSheet* s = new SpriteSheet(*t);
	if (textureName == "Castle2.png")
	{

	}
	else if (textureName == "wood_tileset_3.png")
	{
		sf::Sprite* sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(0,0,32,32)); // only grass
		tiles[TileGame::Grass][TileGame::Grass][TileGame::Grass][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(64,0,32,32));// grass top left
		tiles[TileGame::Grass][TileGame::Grass][TileGame::Earth][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(64,32,32,32)); // horizontal separation (grass left)
		tiles[TileGame::Grass][TileGame::Grass][TileGame::Earth][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(64,64,32,32)); // grass bottom left
		tiles[TileGame::Grass][TileGame::Grass][TileGame::Grass][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(96,0,32,32)); // vertical separation (grass top)
		tiles[TileGame::Grass][TileGame::Earth][TileGame::Earth][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(96,32,32,32));// only earth
		tiles[TileGame::Earth][TileGame::Earth][TileGame::Earth][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(96,64,32,32));// vertical separation (grass bottom)
		tiles[TileGame::Earth][TileGame::Grass][TileGame::Grass][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(128,0,32,32));// grass right top
		tiles[TileGame::Grass][TileGame::Earth][TileGame::Grass][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(128,32,32,32));// horizontal separation (grass right)
		tiles[TileGame::Earth][TileGame::Earth][TileGame::Grass][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(128,64,32,32)); // grass bottom right
		tiles[TileGame::Earth][TileGame::Grass][TileGame::Grass][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(256,192,32,32)); // grass bottom left, top right
		tiles[TileGame::Earth][TileGame::Grass][TileGame::Earth][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(160,224,32,32)); // grass top left, bottom right
		tiles[TileGame::Grass][TileGame::Earth][TileGame::Grass][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(192,224,32,32)); // minimum grass bottom right
		tiles[TileGame::Earth][TileGame::Earth][TileGame::Grass][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(224,224,32,32)); // minimum grass bottom left
		tiles[TileGame::Earth][TileGame::Grass][TileGame::Earth][TileGame::Earth] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(192,256,32,32)); // minimum grass top right
		tiles[TileGame::Earth][TileGame::Earth][TileGame::Earth][TileGame::Grass] = sprite;

		sprite = new sf::Sprite(*t, sf::IntRect(224,256,32,32)); // minimum grass top left
		tiles[TileGame::Grass][TileGame::Earth][TileGame::Earth][TileGame::Earth] = sprite;
	}
	else if (textureName == "BODY_male.png")
	{
		Animation* anim = new Animation();
		anim->setSpriteSheet(*t);
		anim->addFrame(sf::IntRect(0,0,64,64));
		s->addAnimation("idleUp",anim);
		anim = new Animation();
		anim->setSpriteSheet(*t);
		anim->addFrame(sf::IntRect(0,64,64,64));
		s->addAnimation("idleLeft",anim);
		anim = new Animation();
		anim->setSpriteSheet(*t);
		anim->addFrame(sf::IntRect(0,128,64,64));
		s->addAnimation("idleDown",anim);
		anim = new Animation();
		anim->setSpriteSheet(*t);
		anim->addFrame(sf::IntRect(0,192,64,64));
		s->addAnimation("idleRight",anim);

		anim = new Animation();
		anim->setSpriteSheet(*t);
		for (int i = 1; i < 8; ++i)
			anim->addFrame(sf::IntRect(i * 64,0,64,64));
		s->addAnimation("walkUp",anim);
		anim = new Animation();
		anim->setSpriteSheet(*t);
		for (int i = 1; i < 8; ++i)
			anim->addFrame(sf::IntRect(i * 64,64,64,64));
		s->addAnimation("walkLeft",anim);
				anim = new Animation();
		anim->setSpriteSheet(*t);
		for (int i = 1; i < 8; ++i)
			anim->addFrame(sf::IntRect(i * 64,128,64,64));
		s->addAnimation("walkDown",anim);
				anim = new Animation();
		anim->setSpriteSheet(*t);
		for (int i = 1; i < 8; ++i)
			anim->addFrame(sf::IntRect(i * 64,192,64,64));
		s->addAnimation("walkRight",anim);
	}
	textures[textureName] = s;
	return s;
}