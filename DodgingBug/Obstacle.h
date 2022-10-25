#pragma once

#include "header.cpp"

class Obstacle
{
private:
	float moveSpeed;
	float accelerate;
	Texture obsText1;
	Texture obsText2;
	Texture obsText3;
	Texture obsText4;
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

