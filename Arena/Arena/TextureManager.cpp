#include "TextureManager.h"

static TextureManager* _instance;

TextureManager* TextureManager::initialize()
{
	_instance = new TextureManager();
	return _instance;
}

TextureManager* TextureManager::instance()
{
	return _instance;
}


TextureManager::~TextureManager(void)
{
}

sf::Texture* TextureManager::retrieve(const std::string& textureName)
{
	sf::Texture* t = textures[textureName];
	if (t == NULL)
		t = this->load(textureName);
	return t;
}

TextureManager::TextureManager(void)
{
}

sf::Texture* TextureManager::load(const std::string& textureName)
{
	sf::Texture *t = new sf::Texture();
	if (!t->loadFromFile(textureName))
	{
		// BAD!
	}
	textures[textureName] = t;
	return t;
}