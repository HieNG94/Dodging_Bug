#include "Player.h"

void Player::initVariables()
{
	this->moveSpeed = 5.f;
	this->xLeft = 0.f;
	this->yUp = 0.f;
	this->xRight = 50.f;
	this->yDown = 50.f;
	this->state = false;
}

void Player::initPlayer()
{
	if (!this->bugText.loadFromFile("Materials/bug.png")) {
		cout << "Error: Cannot load player image." << endl;
	}
	this->bugSp.setTexture(this->bugText);

	if (!this->bugTextFade.loadFromFile("Materials/bug1.png")) {
		cout << "Error: Cannot load player fadded image." << endl;
	}
}

Player::Player(float x, float y)
{
	this->bugSp.setPosition(x, y);

	this->initVariables();
	this->initPlayer();
}

Player::~Player()
{
}

FloatRect Player::boundingPl()
{
	this->boundingBox = this->bugSp.getGlobalBounds();
	return this->boundingBox;
}

void Player::onHit(bool hit)
{
	if (hit) {
		if (this->state) {
			this->bugSp.setTexture(this->bugText);
			this->state = false;
		}
		else {
			this->state = true;
			this->bugSp.setTexture(this->bugTextFade);
		}
	}
	else
		this->bugSp.setTexture(this->bugText);
}

void Player::updateInput()
{
	this->xLeft = this->bugSp.getPosition().x;
	this->yUp = this->bugSp.getPosition().y;
	this->xRight = xLeft + 50.f;
	this->yDown = yUp + 50.f;

	// Keyboard input
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		if (this->xLeft != 0)
			this->bugSp.move(-this->moveSpeed, 0.f);
		else
			this->bugSp.move(0.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Right)) {
		if (this->xRight != 1380)
			this->bugSp.move(this->moveSpeed, 0.f);
		else
			this->bugSp.move(0.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Up)) {
		if (this->yUp != 50)
			this->bugSp.move(0.f, -this->moveSpeed);
		else
			this->bugSp.move(0.f, 0.f);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Down)) {
		if (this->yDown != 770)
			this->bugSp.move(0.f, this->moveSpeed);
		else
			this->bugSp.move(0.f, 0.f);
	}
}

void Player::update()
{
	// Window bound collision
	this->updateInput();
}

void Player::render(RenderTarget* target)
{
	target->draw(this->bugSp);
}
