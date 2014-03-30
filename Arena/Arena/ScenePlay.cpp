#include "ScenePlay.h"

#include <iostream>

ScenePlay::ScenePlay(sf::RenderWindow* w) : hud(w)
{
	std::cout << "ScenePlay ! " << std::endl;
	window = w;
	SpriteSheet* s = SpriteSheetManager::instance()->retrieve("wood_tileset_3.png");
			
	GameUpdater::TileMap gameTiles;
	for (int x = 0; x < 50; ++x)
	{
		GameUpdater::tileColumn* c = NULL;
		if (gameTiles.count(x))
			c = gameTiles[x];
		for (int y = 0; y < 50; ++y)
		{
			if (!c)
				c = gameTiles[x] = new GameUpdater::tileColumn();
			if (rand() % 3)
				(*c)[y] = new TileGame(TileGame::Grass);
			else
				(*c)[y] = new TileGame(TileGame::Earth);
			//std::cout << "x: " << x << " - - y: " << y << std::endl;
		}
	}

	//std::cout << "new world created! " << std::endl;
	world.tiles = World::mapWorldTilesToSprite(gameTiles);
	//std::cout << "new world converted! " << std::endl;
	worldView = window->getView();
	std::cout << "ScenePlay Loaded! " << std::endl;
}


ScenePlay::~ScenePlay(void)
{

}

void	ScenePlay::update(float elapsedTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		world.gameUpdater.movePlayerUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		world.gameUpdater.movePlayerLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		world.gameUpdater.movePlayerDown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		world.gameUpdater.movePlayerRight();
	world.update(sf::seconds(elapsedTime)); // it will update visually what we know
	stdPairf p = World::worldCoordToSfml(stdPairf(world.playerPosition.x, world.playerPosition.y));

	worldView.setCenter(sf::Vector2f(p.first, p.second));
}

void	ScenePlay::draw(float elapsedTime)
{
	const sf::View& oldView = window->getView();
	window->setView(worldView);
	sf::RenderStates r;
//	r.transform.scale(3,3);
	r.transform.scale(1,1);
	r.transform.translate(-16,-16);
	world.draw(*window, r);
	window->setView(oldView);
	hud.draw(*window);

}