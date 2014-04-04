#include "ScenePlay.h"

#include <iostream>

ScenePlay::ScenePlay(sf::RenderWindow* w) : hud(w), world(*w)
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
	world.dataManager.server.gameTiles = gameTiles;
	world.tiles = World::mapWorldTilesToSprite(gameTiles);
	//std::cout << "new world converted! " << std::endl;
	std::cout << "ScenePlay Loaded! " << std::endl;
}


ScenePlay::~ScenePlay(void)
{

}

void	ScenePlay::update(float elapsedTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		world.dataManager.server.movePlayerUp();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		world.dataManager.server.movePlayerLeft();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		world.dataManager.server.movePlayerDown();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		world.dataManager.server.movePlayerRight();
	world.update(sf::seconds(elapsedTime)); // it will update visually what we know
	stdPairf p = World::worldCoordToSfml(stdPairf(world.playerPosition.x, world.playerPosition.y));

}

void	ScenePlay::updateDraw(float elapsedTime)
{
	world.updateDraw(sf::seconds(elapsedTime));
}

void	ScenePlay::draw(float elapsedTime)
{
	const sf::View& oldView = window->getView();

	window->setView(world.worldView);
	sf::RenderStates r;
	r.transform.scale(1,1);
	//r.transform.scale(1,1);
	//r.transform.translate(-16,-16);
	world.draw(*window, r);
	window->setView(oldView);
	hud.draw(*window);

}