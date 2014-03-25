#include "ScenePlay.h"


ScenePlay::ScenePlay(sf::RenderWindow* w) : hud(w)
{
	window = w;
}


ScenePlay::~ScenePlay(void)
{
}

void	ScenePlay::update(float elapsedTime)
{

}

void	ScenePlay::draw(float elapsedTime)
{
	sf::RenderStates r;
//	r.transform.scale(3,3);
	r.transform.scale(1,1);
	
	hud.draw(*window, r);
}