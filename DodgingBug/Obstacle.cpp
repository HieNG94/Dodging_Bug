#include "Obstacle.h"

void Obstacle::initVariables()
{
	this->moveSpeed = rand() % 2 + 1;
	this->scale = 0.5f;
	srand(time(NULL));
}

void Obstacle::initObstacle()
{
	if (!this->obsText1.loadFromFile("Materials/object1.png")) {
		cout << "Error: Cannot load obstacle." << endl;
	}
	if (!this->obsText2.loadFromFile("Materials/object2.png")) {
		cout << "Error: Cannot load obstacle." << endl;
	}
	if (!this->obsText3.loadFromFile("Materials/object3.png")) {
		cout << "Error: Cannot load obstacle." << endl;
	}
	if (!this->obsText4.loadFromFile("Materials/object4.png")) {
		cout << "Error: Cannot load obstacle." << endl;
	}
}

Obstacle::Obstacle()
{
	this->initVariables();
	this->initObstacle();

	this->spawnObstacle();
}

Obstacle::~Obstacle()
{
}

void Obstacle::spawnObstacle()
{
	switch (rand() % 4) {
	case 0:
		this->obsSp.setTexture(this->obsText1);
		break;
	case 1:
		this->obsSp.setTexture(this->obsText2);
		break;
	case 2:
		this->obsSp.setTexture(this->obsText3);
		break;
	case 3:
		this->obsSp.setTexture(this->obsText4);
		break;
	}

	this->moveSpeed = rand() % 4 + 2;
	this->obsSp.setPosition(1440, rand() % 700 + 50);
	this->obsSp.setOrigin(25.f, 25.f);
	this->obsSp.setRotation(rand());
	this->obsSp.setScale(this->scale, this->scale);

	if (this->scale >= 1.2f)
		this->scale = 0.5f;
	else
		this->scale += 0.1f;
}

bool Obstacle::isHit(FloatRect pl)
{
	this->boundingBox = this->obsSp.getGlobalBounds();
	if (this->boundingBox.intersects(pl))
		return true;
	return false;
}

void Obstacle::updateObstacle()
{
	if (this->obsSp.getPosition().x <= -50.f) {
		this->spawnObstacle();
	}
	this->obsSp.move(-this->moveSpeed, 0.f);
}

void Obstacle::update()
{
	this->updateObstacle();
}

void Obstacle::render(RenderTarget* target)
{
	target->draw(this->obsSp);
}
