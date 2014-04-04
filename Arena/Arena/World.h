#pragma once

#include <map>
#include<SFML\Graphics.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Tile.h"
#include "TileGame.h"

#include "GameDataManager.h"	
#include "GameUpdater.h"


typedef std::pair<float, float> stdPairf;
typedef std::pair<int, int> stdPairi;

class World : public sf::Drawable, public sf::Transformable
{
public:
	static stdPairf worldCoordToSfml(const stdPairf& wc);
	static stdPairf worldCoordToSfml(const stdPairi& wc);
	static stdPairf sfmlCoordToWorld(const stdPairf& sc);

	static std::map<stdPairi , sf::Sprite* >* mapWorldTilesToSprite(GameUpdater::TileMap& worldMap);

	World(sf::RenderWindow&);
	~World(void);
	std::map<std::pair<int, int>, sf::Sprite*>* tiles;
	void update(const sf::Time&);
	void updateDraw(const sf::Time&); // update only visual things, no game logic
	void draw(sf::RenderTarget&, sf::RenderStates)const;

	sf::Vector2f playerPosition;
	sf::RenderWindow& w;
	//GameUpdater gameUpdater; // this represents the server
	GameDataManager dataManager;
	sf::View worldView;
private:
	AnimatedSprite* player;
	std::string currentAnimation;

};

