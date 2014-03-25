#include "MenuWelcome.h"


MenuWelcome::MenuWelcome(int w, int h) : width(w), height(h)
{
	if (!f.loadFromFile("orangejuice2.0.ttf"))
		system("PAUSE");
	playText.setFont(f);
	playText.setString("Play");
	
	playText.setPosition(w / 2 - playText.getLocalBounds().width / 2,
		h / 2 - playText.getLocalBounds().height / 2);
}


MenuWelcome::~MenuWelcome(void)
{
}

void MenuWelcome::draw(sf::RenderWindow& window){
	playText.setColor(sf::Color::Blue);
	window.draw(playText);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (playText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		{
			SceneManager::instance()->pushScene(new ScenePlay(&window));
		}
	}
}