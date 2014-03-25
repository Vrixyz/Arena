#pragma once

#include <SFML\Graphics.hpp>

#include "ILayer.h"

#include "HealthSprite.h"

class LayerHud : 
	public ILayer, public sf::Drawable, public sf::Transformable
{
public:
	LayerHud(sf::RenderTarget* w);
	~LayerHud(void);
	virtual void draw();
	virtual void draw( sf::RenderTarget&, sf::RenderStates states = sf::RenderStates::Default) const;

private:
	sf::RenderTarget* renderTarget;
	sf::View view;
	HealthSprite s_health;
};

