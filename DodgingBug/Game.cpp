#include "Game.h"

void Game::initVariables()
{
	this->window = nullptr;
	this->point = 0;
	this->hp = MAX_HP;
	this->hit = false;
	this->justStart = true;
	this->start = high_resolution_clock::now();
	srand(time(NULL));
}

void Game::initWindow()
{
	this->videoMode.height = 770;
	this->videoMode.width = 1380;
	this->window = new RenderWindow(this->videoMode, "Dodging Bug", Style::Close);
	this->window->setFramerateLimit(120);
}

void Game::initWorld() {
	if (!this->worldText.loadFromFile("Materials/normal-bg.png")) {
		cout << "Error: Cannot load the background image." << endl;
		this->window->close();
	}
	this->worldBackground.setTexture(this->worldText);
	this->worldBackground.setPosition(Vector2f(0.f, 50.f));
	this->worldBackground1.setTexture(this->worldText);
	this->worldBackground1.setPosition(Vector2f(1380.f, 50.f));
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Materials/slkscre.ttf")) {
		cout << "Error: Cannot load font" << endl;
		this->window->close();
	}

	if (!this->fontEnd.loadFromFile("Materials/startFont.ttf")) {
		cout << "Error: Cannot load font" << endl;
		this->window->close();
	}
}

void Game::initText()
{
	this->textPoint.setFont(this->font);
	this->textPoint.setFillColor(Color::Black);
	this->textPoint.setCharacterSize(35);
	this->textPoint.setPosition(Vector2f(10.f, 0.f));
	this->textPoint.setString("Point: ");

	this->textHp.setFont(this->font);
	this->textHp.setFillColor(Color::Black);
	this->textHp.setCharacterSize(35);
	this->textHp.setPosition(Vector2f(790.f, 0.f));
	this->textHp.setString("HP ");

	this->textEnd.setFont(this->fontEnd);
	this->textEnd.setFillColor(Color::Red);
	this->textEnd.setCharacterSize(100);
	this->textEnd.setPosition(Vector2f(400.f, 400.f));
	this->textEnd.setString("GAME OVER!");

	this->textEnd.setFont(this->fontEnd);
	this->textEnd.setFillColor(Color::Red);
	this->textEnd.setCharacterSize(100);
	this->textEnd.setPosition(Vector2f(200.f, 250.f));
	this->textEnd.setString("GAME OVER!");

	this->textEndPoint.setFont(this->fontEnd);
	this->textEndPoint.setFillColor(Color::Red);
	this->textEndPoint.setCharacterSize(50);
	this->textEndPoint.setPosition(Vector2f(200.f, 350.f));

	this->retry.setFont(this->fontEnd);
	this->retry.setFillColor(Color::Red);
	this->retry.setCharacterSize(50);
	this->retry.setPosition(Vector2f(200.f, 400.f));
	this->retry.setString("[F1] to Retry");
}

void Game::initGUI()
{
	this->hpBarBorder.setSize(Vector2f(500.f, 30.f));
	this->hpBarBorder.setOutlineColor(Color::Black);
	this->hpBarBorder.setOutlineThickness(5.f);
	this->hpBarBorder.setPosition(Vector2f(860.f, 10.f));

	this->hpBar.setFillColor(Color::Red);
	this->hpBar.setPosition(Vector2f(860.f, 10.f));
}


Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initWorld();
	this->initText();
	this->initFont();
	this->initGUI();
}

Game::~Game() {
	delete this->window;
}

const bool Game::running()
const {
	return this->window->isOpen();
}

void Game::pollEvent() {
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type) {
		case Event::Closed:
			this->window->close();
			break;
		case Event::KeyPressed:
			if (this->ev.key.code == Keyboard::Escape)
				this->window->close();
			else if (this->ev.key.code == Keyboard::F1) {
				this->point = 0;
				this->hp = MAX_HP;
				this->hit = false;
				this->justStart = true;
				this->start = high_resolution_clock::now();
				this->worldBackground.setPosition(Vector2f(0.f, 50.f));
				this->worldBackground1.setPosition(Vector2f(1380.f, 50.f));
				for (int i = 0; i < this->MAX_OBSTACLES; i++)
					this->obs[i].spawnObstacle();
			}
			break;
		}
	}
}

void Game::update() {
	this->pollEvent();
	if (this->hp > 0) {
		this->updateGUI();
		this->updateWorld();
		this->player.update();
		this->updateHit();

		if (!this->justStart)
		{
			for (int i = 0; i < this->MAX_OBSTACLES; i++) {
				this->obs[i].update();
				if (this->obs[i].isHit(this->player.boundingPl())) {
					if (!this->hit) {
						this->start = high_resolution_clock::now();
						this->hp -= 1.f;
						this->hit = true;
					}
				}
			}
		}
		else {
			this->end = high_resolution_clock::now();
			if (duration_cast<float_second>(this->end - this->start).count() > 5.f)
				this->justStart = false;
		}
	}
}

void Game::updateHit()
{
	this->player.onHit(this->hit);

	if (this->hit == true) {
		this->end = high_resolution_clock::now();
		if (duration_cast<float_second>(this->end - this->start).count() > 5.f)
			this->hit = false;
	}
}

void Game::updateGUI()
{
	// Update point
	stringstream ss;
	ss << "Point: " << this->point;
	this->textPoint.setString(ss.str());

	// Update HP bar
	this->hpBar.setSize(Vector2f(500.f * (this->hp / 10), 30.f));
}

void Game::updateWorld()
{
	if (this->worldBackground.getPosition().x + 1380 <= 0) {
		this->worldBackground.setPosition(Vector2f(1380.f, 50.f));
		this->point += 200;
	}
	this->worldBackground.move(Vector2f(-1.f, 0.f));

	if (this->worldBackground1.getPosition().x + 1380 <= 0) {
		this->worldBackground1.setPosition(Vector2f(1380.f, 50.f));
		this->point += 200;
	}
	this->worldBackground1.move(Vector2f(-1.f, 0.f));
}


void Game::renderGUI()
{
	this->window->draw(this->textPoint);
	this->window->draw(this->textHp);
	this->window->draw(this->hpBarBorder);
	this->window->draw(this->hpBar);
}

// Create game background and maze 
void Game::renderWorld() {
	this->window->draw(this->worldBackground);
	this->window->draw(this->worldBackground1);
}

void Game::render() {
	if (this->hp > 0) {
		this->window->clear(Color(165, 250, 247, 1));

		// Draw game window
		this->renderWorld();
		this->renderGUI();

		// Draw player
		this->player.render(this->window);

		// Draw obstacles
		for (int i = 0; i < this->MAX_OBSTACLES; i++)
			this->obs[i].render(this->window);
	}
	else {
		this->window->draw(this->textEnd);
		stringstream ss;
		ss << this->point << " Pts.";
		this->textEndPoint.setString(ss.str());
		this->window->draw(this->textEndPoint);
		this->window->draw(this->retry);
	}

	// Draw game objects
	this->window->display();
}