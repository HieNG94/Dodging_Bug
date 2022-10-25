#pragma once

#include "header.cpp"

class Enemy
{
private:
	Texture enemyText;
	Sprite enemySp;

	void initVariable();
	void initEnemy();
public:
	Enemy();
	virtual ~Enemy();
	void update();
	void updateEnemy();
	void renderEnemy();
	void render();
};

