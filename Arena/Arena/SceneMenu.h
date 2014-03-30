#pragma once

#include <SFML\Graphics.hpp>

#include "main.h"
#include "Iscene.h"
#include "MenuWelcome.h"

class SceneMenu :
	public IScene
{
public:
	SceneMenu(sf::RenderWindow* w);
	virtual ~SceneMenu(void);

	virtual void update(float elapsedTime);
	virtual void updateDraw(float elapsedTime);
	virtual void draw(float elapsedTime);
private:
	sf::RenderWindow* window;

	MenuWelcome menuWelcome;
};