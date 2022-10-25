#pragma once

#include "header.cpp"

class Start
{
private:
	float moveSpeed;
	float moveSpeedMax;
	bool startGame;
	int count;
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	Texture worldText;
	Sprite worldBackground;
	Texture playerTx;
	Sprite playerSp;
	Text title;
	Text opt1;
	Font font;
	float xLeft;
	float xRight;

	void initVariables();
	void initWindow();
	void initWorld();
	void initPlayer();
	void initFont();
	void initText();

public:
	Start();
	virtual ~Start();

	//Acceccors
	const bool running() const;

	void pollEvent();
	bool getStart();
	void updateOpt();
	void updatePlayer();
	void update();
	void render();
};

