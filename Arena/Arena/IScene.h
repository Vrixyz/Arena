#pragma once

class IScene
{
public:
	virtual void update(float elapsedTime) = 0;
	virtual void updateDraw(float elapsedTime) = 0;
	virtual void draw(float elapsedTime) = 0;
};

