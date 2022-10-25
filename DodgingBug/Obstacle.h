#pragma once

#include "header.cpp"

class Obstacle
{
private:
	float moveSpeed;
	Texture obsText;
	Sprite obsSp;
	FloatRect boundingBox;
	float scale;

	void initVariables();
	void initObstacle();
public:
	Obstacle();
	virtual ~Obstacle();
	void spawnObstacle();
	bool isHit(FloatRect);
	void updateObstacle();
	void update();
	void render(RenderTarget*);
};

