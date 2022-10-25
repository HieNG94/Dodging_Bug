#include "Start.h"

void Start::initVariables()
{
	this->moveSpeed = 5.f;
	this->startGame = true;
	this->count = 0;
}

void Start::initWindow()
{
	this->videoMode.height = 770;
	this->videoMode.width = 1380;
	this->window = new RenderWindow(this->videoMode, "Dodging Bug", Style::Close);
	this->window->setFramerateLimit(120);
}

void Start::initWorld()
{
	if (!this->worldText.loadFromFile("Materials/normal-bg.png")) {
		cout << "Error: Cannot load the background image." << endl;
		this->window->close();
	}
	this->worldBackground.setTexture(this->worldText);
	this->worldBackground.setPosition(Vector2f(0.f, 50.f));
}

void Start::initPlayer()
{
}

void Start::initFont()
{
	if (!this->font.loadFromFile("Materials/startFont.ttf")) {
		cout << "Error: Cannot load font" << endl;
		this->window->close();
	}
}

void Start::initText()
{
	this->title.setFont(this->font);
	this->title.setFillColor(Color(6, 40, 61));
	this->title.setCharacterSize(100);
	this->title.setPosition(Vector2f(200.f, 20.f));
	this->title.setString("DODGING BUG");

	this->opt1.setFont(this->font);
	this->opt1.setFillColor(Color(6, 40, 61));
	this->opt1.setCharacterSize(50);
	this->opt1.setPosition(Vector2f(380.f, 600.f));
	this->opt1.setString("[Enter] to Start");
}

Start::Start()
{
	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initText();
	this->initFont();
}

Start::~Start()
{
	delete this->window;
}

const bool Start::running() const
{
	return this->window->isOpen();
}

void Start::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
		case Event::Closed:
			this->startGame = false;
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape) {
				this->startGame = false;
				this->window->close();
			}
			if (this->ev.key.code == Keyboard::Enter) {
				this->window->close();
			}
			break;
		}
	}
}

bool Start::getStart()
{
	return this->startGame;
}

void Start::updateOpt()
{
	if (this->count == 20) {
		this->opt1.setFillColor(Color(6, 40, 61));
		this->count++;
	}
	else if (this->count == 40) {
		this->opt1.setFillColor(Color(37, 109, 133));
		this->count++;
	}
	else if (this->count == 60) {
		this->opt1.setFillColor(Color(71, 181, 255));
		this->count = 0;
		this->count++;
	}
	else
		this->count++;
}

void Start::update()
{
	this->pollEvent();
	this->updateOpt();
}

void Start::render()
{
	this->window->clear(Color(165, 250, 247, 1));

	// Draw game window
	this->window->draw(this->worldBackground);
	this->window->draw(this->title);
	this->window->draw(this->opt1);

	// Draw player


	// Draw game objects
	this->window->display();
}
