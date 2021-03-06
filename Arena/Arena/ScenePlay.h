#pragma once

#include <SFML\Graphics.hpp>

#include "IScene.h"

#include "LayerHud.h"
#include "World.h"
#include "TileGame.h"

class ScenePlay :
	public IScene
{
public:
	ScenePlay(sf::RenderWindow* w);
	virtual ~ScenePlay(void);

	virtual void update(float elapsedTime);
	virtual void updateDraw(float elapsedTime);
	virtual void draw(float elapsedTime);

private:
	sf::RenderWindow* window;
	LayerHud hud;
	World world;
};

