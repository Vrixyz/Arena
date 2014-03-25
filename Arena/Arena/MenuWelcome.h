#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

#include "SceneManager.h"
#include "ScenePlay.h"

class MenuWelcome
{
public:
	MenuWelcome(int w, int h);
	~MenuWelcome(void);

	void draw(sf::RenderWindow& window);

private:
	int width;
	int height;
	sf::Text playText;
	sf::Font f;
};

