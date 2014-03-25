#pragma once

#include <string>
#include <map>

#include <SFML\Graphics.hpp>

class TextureManager
{
public:

	static TextureManager* initialize();
	static TextureManager* instance();

	~TextureManager(void);

	sf::Texture* retrieve(const std::string& textureName);
	// maybe add a release ? (so an unload in private)
private:
	std::map<std::string, sf::Texture*> textures;

	TextureManager(void);

	sf::Texture* load(const std::string& textureName);
};

