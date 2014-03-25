#pragma once

#include <list>

#include "IScene.h"

class SceneManager
{
public:
	static SceneManager* initialize();

	/// <summary>Make sure you called initialize() before<summary>
	static SceneManager* instance();

	~SceneManager(void);

	IScene* getCurrentScene();
	void popScene();
	void pushScene(IScene* scene);

private:
	std::list<IScene*> scenes; // ugly double linked list

	SceneManager(void);
};

