#include <SFML/Graphics.hpp>

#include "main.h"
#include "MenuWelcome.h"
#include "SceneManager.h"
#include "SceneMenu.h"

typedef enum GameState_e {
	welcome,
	play,
	pause
} GameState;

static GameState gameState;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML works!");

	SceneManager* sceneManager = SceneManager::initialize();
	SpriteSheetManager* spriteSheetManager = SpriteSheetManager::initialize();

	sceneManager->pushScene(new SceneMenu(&window));


	sf::Clock clockUpdate;
	sf::Clock clockDraw;

	float updateRate = (float)1 / ((60 / 2) / 2); // every 4 draw, we update ( ~ 0.066 )
	float drawRate = (float)1 / 60; // 60 times per second ( ~ 0.0166 )
	std::cout << updateRate << std::endl;
	std::cout << drawRate << std::endl;
    while (window.isOpen())
    {
		sf::Time elapsed = clockUpdate.getElapsedTime();
		if (elapsed.asSeconds() > updateRate) 
		{
			elapsed = clockUpdate.restart();
			//::cout << "Update ! " << elapsed.asSeconds() << std::endl;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			SceneManager::instance()->getCurrentScene()->update(elapsed.asSeconds());
		}
		elapsed = clockDraw.getElapsedTime();
		if (elapsed.asSeconds() > drawRate) // 60 times per second, let's draw
		{
			elapsed = clockDraw.restart();
			//std::cout << "Draw: " << elapsed.asSeconds() << std::endl;
			window.clear(sf::Color::White);
			SceneManager::instance()->getCurrentScene()->draw(elapsed.asSeconds());
			window.display();
		}

		sf::sleep(sf::seconds(drawRate)); // maybe it's a high sleep but let's see if it's noticeable...
    }

    return 0;
}