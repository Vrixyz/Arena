#pragma once
#include <SFML\Graphics.hpp>

#include "TextureManager.h"

class HealthSprite :
	public sf::Drawable, public sf::Transformable
{
public:
	HealthSprite(void);
	~HealthSprite(void);

	virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
	int maxRed;
	int currentRed;
	int maxBlue;
	int currentBlue;
private:
	void drawEmptyJauges(sf::RenderTarget& r, const sf::RenderStates& states) const;
	void drawReds(sf::RenderTarget& r, sf::RenderStates states) const;
	void drawBlues(sf::RenderTarget& r, sf::RenderStates states) const;
	sf::Texture* texture;
	sf::Sprite container;
	sf::Sprite firstEmptyJauge;
	sf::Sprite emptyJauge;
	sf::Sprite firstRedJauge;
	sf::Sprite fullRedJauge;
	sf::Sprite endJaugeRed;
	sf::Sprite firstBlueJauge;
	sf::Sprite fullBlueJauge;
	sf::Sprite endJaugeBlue;
};

