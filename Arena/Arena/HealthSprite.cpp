#include "HealthSprite.h"


HealthSprite::HealthSprite(void) : Drawable(), sf::Transformable(),
	texture(TextureManager::instance()->retrieve("gold_HUD.png")),
	container(*texture, sf::IntRect(447, 179, 85, 65)),
	firstEmptyJauge(*texture, sf::IntRect(533, 184, 8, 16)),
	emptyJauge(*texture, sf::IntRect(542, 184, 8, 16)),
	firstRedJauge(*texture, sf::IntRect(592, 184,8, 16)),
	fullRedJauge(*texture, sf::IntRect(601, 184, 8, 16)),
	endJaugeRed(*texture, sf::IntRect(551, 182, 32, 20)),
	firstBlueJauge(*texture, sf::IntRect(592, 204, 8, 16)),
	fullBlueJauge(*texture, sf::IntRect(601, 204, 8, 16)),
	endJaugeBlue(*texture, sf::IntRect(551, 202, 32, 20))
{
	emptyJauge.setPosition(85, 5);
	firstRedJauge.setPosition(85, 5);
	fullRedJauge.setPosition(85, 5);
	endJaugeRed.setPosition(85, 3);
	firstBlueJauge.setPosition(85, 25);
	fullBlueJauge.setPosition(85, 25);
	endJaugeBlue.setPosition(85, 3);
	maxRed = 3;
	currentRed = 3;
	maxBlue = 6;
	currentBlue = 4;
}


HealthSprite::~HealthSprite(void)
{
}


void HealthSprite::draw(sf::RenderTarget& r, sf::RenderStates states) const
{
	states.transform *= getTransform();
	r.draw(container, states);
	drawEmptyJauges(r, states);
	drawReds(r, states);
	drawBlues(r, states);
}

void HealthSprite::drawEmptyJauges(sf::RenderTarget& r, const sf::RenderStates& states) const
{
	sf::RenderStates tmpState(states);
	for (int i = 0; i < maxRed; ++i)
	{
		r.draw(emptyJauge, tmpState);
		tmpState.transform.translate(emptyJauge.getLocalBounds().width, 0);
	}
	r.draw(endJaugeRed, tmpState);
	tmpState = states;
	tmpState.transform.translate(0, 20);
	if (maxBlue > 0)
	{
		r.draw(emptyJauge, tmpState);
	}
	for (int i = 1; i < maxBlue; ++i)
	{
		tmpState.transform.translate(emptyJauge.getLocalBounds().width, 0);
		r.draw(emptyJauge, tmpState);
	}
	tmpState.transform.translate(emptyJauge.getLocalBounds().width, 0);
	r.draw(endJaugeBlue, tmpState);
}

void HealthSprite::drawReds(sf::RenderTarget& r, sf::RenderStates states) const
{
	if (currentRed > 0)
	{
		r.draw(firstRedJauge, states);
	}
	for (int i = 1; i < currentRed; ++i)
	{
		states.transform.translate(fullRedJauge.getLocalBounds().width, 0);
		r.draw(fullRedJauge, states);
	}
}
void HealthSprite::drawBlues(sf::RenderTarget& r, sf::RenderStates states) const
{
	if (currentBlue > 0)
	{
		r.draw(firstBlueJauge, states);
	}
	for (int i = 1; i < currentBlue; ++i)
	{
		states.transform.translate(fullBlueJauge.getLocalBounds().width, 0);
		r.draw(fullBlueJauge, states);
	}
}