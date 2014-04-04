#include "World.h"

#include <iostream>

stdPairf World::worldCoordToSfml(const stdPairf& wc)
{
	return stdPairf(wc.first * 32, wc.second * -32);
}
stdPairf World::worldCoordToSfml(const stdPairi& wc)
{
	//std::cout << wc.first << ";" << wc.second <<  " - - " << (float)wc.first * 32 << ";" << (float)wc.second * -32 << std::endl;
	return stdPairf((float)(wc.first) * 32, (float)wc.second * -32);
}

stdPairf World::sfmlCoordToWorld(const stdPairf& sc)
{
	return stdPairf(sc.first / 32, -sc.second / 32);
}


World::World(sf::RenderWindow& _w) : w(_w)
{
	SpriteSheet* sCharacter = SpriteSheetManager::instance()->retrieve("BODY_male.png");
	player = new AnimatedSprite();
	player->setAnimation(*sCharacter->getAnimation("idleDown"));
	currentAnimation = "idleDown";
	worldView = w.getView();
}


World::~World(void)
{
}

void World::update(const sf::Time& elapsedTime)
{

	SpriteSheet* sCharacter = SpriteSheetManager::instance()->retrieve("BODY_male.png");
	
	playerPosition.x = dataManager.server.getPlayerPosition()[0];
	playerPosition.y = dataManager.server.getPlayerPosition()[1];
	if (dataManager.server.playerSpeed[0] == 0 && dataManager.server.playerSpeed[1] == 0)
		{
			if (currentAnimation.compare(0, 4, "idle") != 0)
			{
				
				std::string newAnim = "idle" + currentAnimation.substr(4);
				std::cout << "idling !! " << newAnim << std::endl;
				currentAnimation = newAnim;
				player->setAnimation(*sCharacter->getAnimation(newAnim));
			}
	}
	else if (dataManager.server.playerSpeed[0] > 0)
	{
			if (currentAnimation != "walkRight")
			{
				currentAnimation = "walkRight";
				player->setAnimation(*sCharacter->getAnimation("walkRight"));
			}
	}
	else if (dataManager.server.playerSpeed[0] < 0)
	{
			if (currentAnimation != "walkLeft")
			{
				currentAnimation = "walkLeft";
				player->setAnimation(*sCharacter->getAnimation("walkLeft"));
			}
	}
	else if (dataManager.server.playerSpeed[1] > 0)
	{
			if (currentAnimation != "walkUp")
			{
				currentAnimation = "walkUp";
				player->setAnimation(*sCharacter->getAnimation("walkUp"));
			}
	}
	else
	{
			if (currentAnimation != "walkDown")
			{
				currentAnimation = "walkDown";
				player->setAnimation(*sCharacter->getAnimation("walkDown"));
			}
	}
	sf::Vector2i mousePos = sf::Mouse::getPosition(w);
	mousePos.x -= w.getSize().x / 2;
	mousePos.y -= w.getSize().y / 2;

	sf::Vector2f playerPos = dataManager.getPlayerposition();

	stdPairf sfmlPlayerPos = World::worldCoordToSfml(stdPairf(playerPos.x, playerPos.y));
	sf::Vector2f newCamPos( mousePos.x + sfmlPlayerPos.first, mousePos.y + sfmlPlayerPos.second);
	worldView.setCenter(newCamPos);

	mousePos *= 2; // This is a shortcut, because our camera is always at half our distance from mouse, so we can just double it.
	stdPairf wPlayerRelPos = World::sfmlCoordToWorld(stdPairf((float)mousePos.x, (float)mousePos.y));
	dataManager.server.setRelativeAimPoint(wPlayerRelPos.first, wPlayerRelPos.second);

	
	//std::cout << "relative pos : " << wPlayerRelPos.first << ";" << wPlayerRelPos.second << std::endl;
	//std::cout << "mouse pos : " << mousePos.x << ";" << mousePos.y << std::endl;
	//std::cout << "relative pos : " << playerPos.x << ";" << playerPos.y << std::endl;
	//std::cout << "relative pos : " << sfmlPlayerPos.first << ";" << sfmlPlayerPos.second << std::endl;
	
	GameUpdater::TileMap* m = dataManager.getKnownTiles();
	delete tiles;
	this->tiles = World::mapWorldTilesToSprite(*m);
	delete m;
	dataManager.update(elapsedTime.asSeconds()); // server will do that
}

void World::updateDraw(const sf::Time& elapsedTime)
{
		player->update(elapsedTime);
}

void	World::draw(sf::RenderTarget& rt, sf::RenderStates s)const
{


	for (auto keyvalue : *tiles)
	{
		sf::RenderStates state = s;
		sf::Transform t;
		stdPairf toTransl = World::worldCoordToSfml(stdPairf((float)keyvalue.first.first, (float)keyvalue.first.second));
		t.translate(toTransl.first, toTransl.second);
		t.translate(0, -32); // because sprite is drawn from top left, and I want them bottom left (like regular x/y axis, where my [0][0] sprite tile is between [0][0] and [1][1] in game.

		//std::cout << keyvalue.first.first << " : " << ((float)(keyvalue.first.first) / 1) * 32 << std::endl;
		t.combine(s.transform);
		if (keyvalue.second)
			rt.draw(*keyvalue.second, t);
	}
	//std::cout << " " << std::endl;
	sf::RenderStates state = s;
	sf::Transform t;
	stdPairf toTranslate = World::worldCoordToSfml(stdPairf(playerPosition.x, playerPosition.y));
	t.translate(toTranslate.first, toTranslate.second);
	
	t.combine(s.transform);
	t.translate(-32, -62); // so center of its feet are at the point
	rt.draw(*player, t);
}

std::map<stdPairi, sf::Sprite*>* World::mapWorldTilesToSprite(GameUpdater::TileMap& gameTiles)
{
	std::map<stdPairi, sf::Sprite*>* spriteMap = new std::map<stdPairi, sf::Sprite*>();
	
	//for (auto gt : gameTiles)
	for (auto column : gameTiles)
	{
		int x = column.first;
		//std::cout << "x: " << x << std::endl;
			for (auto tile : *column.second)
				{
					int y = tile.first;
					//std::cout << "x: " << x << " ; y: " << y << std::endl;

					TileGame::tileType upLeft(TileGame::Unknown);
					TileGame::tileType downLeft(TileGame::Unknown);
					TileGame::tileType downRight(TileGame::Unknown);
					TileGame::tileType upRight(TileGame::Unknown);

					if (gameTiles.count(x) && (*gameTiles[x]).count(y + 1))
					{
						if ((*gameTiles[x])[y + 1])
							upLeft = (*gameTiles[x])[y + 1]->type;
					}
					if (tile.second)
						downLeft = tile.second->type;
					if (gameTiles.count(x + 1) && (*gameTiles[x + 1]).count(y))
						if ((*gameTiles[x + 1])[y])
							downRight =  (*gameTiles[x + 1])[y]->type;
					if (gameTiles.count(x + 1) && (*gameTiles[x + 1]).count(y + 1))
						if ((*gameTiles[x + 1])[y + 1])
							upRight = (*gameTiles[x + 1])[y + 1]->type;
					sf::Sprite* toAdd = SpriteSheetManager::instance()->getTile(upLeft,downLeft, downRight, upRight);
					//std::cout << "upleft: " << upLeft << " ; "
					//	<< "downLeft: " << downLeft << " ; "
					//	<< "downRight: " << downRight << " ; "
					//	<< "upRight: " << upRight << " : " << toAdd << std::endl;
					//system("PAUSE");
					if (toAdd)
						(*spriteMap)[stdPairi(x,y)] = toAdd;
				}
	}
	return spriteMap;
}