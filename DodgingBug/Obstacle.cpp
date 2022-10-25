#include "Obstacle.h"

void Obstacle::initVariables()
{
	this->moveSpeed = rand() % 2 + 1;
	this->scale = 0.5f;
}

void Obstacle::initObstacle()
{/*
	switch (this->getRandNum() % ) {

	}*/
	if (!this->obsText.loadFromFile("Materials/object1.png")) {
		cout << "Error: Cannot load obstacle." << endl;
	}
	this->obsSp.setTexture(this->obsText);
}

Obstacle::Obstacle()
{
	this->spawnObstacle();

	this->initVariables();
	this->initObstacle();
}

Obstacle::~Obstacle()
{
}

void Obstacle::spawnObstacle()
{
	this->moveSpeed = rand() % 6 + 2;
	this->obsSp.setPosition(1380, rand() % 700 + 50);
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
	if (this->obsSp.getPosition().x <= -50.f)
		this->spawnObstacle();
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
