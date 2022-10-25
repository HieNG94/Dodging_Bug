#pragma once

#include "header.cpp"

class Start
{
private:
	float moveSpeed;
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
	void update();
	void render();
};

