#include "SceneMenu.h"


SceneMenu::SceneMenu(sf::RenderWindow* w) : menuWelcome(w->getSize().x, w->getSize().y)
{
	window = w;
}


SceneMenu::~SceneMenu(void)
{
}

void SceneMenu::update(float elapsedTime)
{

}

void SceneMenu::updateDraw(float elapsedTime)
{

}

void SceneMenu::draw(float elapsedTime)
{
	menuWelcome.draw(*window);
}