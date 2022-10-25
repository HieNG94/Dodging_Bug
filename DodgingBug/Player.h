#pragma once

#include "header.cpp"

class Player
{
private:
	float moveSpeed;
	float xLeft;
	float yUp;
	float xRight;
	float yDown;
	bool state;

	Texture bugText;
	Texture bugTextFade;
	Sprite bugSp;
	FloatRect boundingBox;
	void initVariables();
	void initPlayer();
public:
	Player(float x = 0.f, float y = 410.f);
	virtual ~Player();
	FloatRect boundingPl();
	void onHit(bool);
	void updateInput();
	void update();
	void render(RenderTarget*);
};

