#include "SceneManager.h"

static SceneManager* _instance;



SceneManager* SceneManager::initialize()
{
	_instance = new SceneManager();
	return _instance;
}

SceneManager* SceneManager::instance()
{
	return _instance;
}

SceneManager::~SceneManager(void)
{
}

IScene* SceneManager::getCurrentScene()
{
	return scenes.front();
}

void SceneManager::popScene()
{
	scenes.pop_front();
}

void SceneManager::pushScene(IScene* scene)
{
	scenes.push_front(scene);
}

SceneManager::SceneManager(void)
{
}