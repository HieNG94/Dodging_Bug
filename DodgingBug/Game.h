#pragma once

#include "header.cpp"
#include "Player.h"
#include "Enemy.h"
#include "Obstacle.h"

class Game
{
private:
	// Variables
	int point;
	float hp;
	const float MAX_HP = 10.f;
	const int MAX_OBSTACLES = 10;
	bool hit;
	time_point<high_resolution_clock> start, end;
	typedef duration<float> float_second;

	// Window
	RenderWindow* window;
	VideoMode videoMode;
	Event ev;
	Texture worldText;
	Sprite worldBackground;
	Sprite worldBackground1;
	Text textPoint;
	Text textHp;
	Font font;
	RectangleShape hpBarBorder;
	RectangleShape hpBar;
	Player player;
	Obstacle obs[10]; 

	//Private fuctions
	void initVariables();
	void initWindow();
	void initWorld();
	void initFont();
	void initText();
	void initGUI();
public:
	// Constructors / Destructors
	Game();
	virtual ~Game();

	//Acceccors
	const bool running() const;

	// Function 
	void pollEvent();
	void update();
	void updateHit();
	void updateGUI();
	void updateWorld();
	void renderGUI();
	void renderWorld();
	void render();
};

