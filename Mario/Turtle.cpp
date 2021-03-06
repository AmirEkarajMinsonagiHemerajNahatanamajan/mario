#include "Turtle.h"

SDL_Surface* Turtle::turtleImages[4] = { nullptr };

void Turtle::chooseModel() {
	++this->changeModelCounter;
	if (this->changeModelCounter % 30 == 0) {
		this->model += (this->model & 1 ? 1 : -1);
	}
}

Turtle::Turtle() {}

Turtle::Turtle(int x, int y) {
	this->width = 26;
	this->height = 38;
	this->positionX = x;
	this->positionY = y;
	this->model = 1;
	this->stepsCounter = 0;
	this->changeModelCounter = 0;
	this->moveDirection = None;
}

void Turtle::setMoveDirection(Direction direction) {
	this->moveDirection = direction;
}

void Turtle::loadTurtleImages(SDL_Surface* screen) {
	turtleImages[0] = loadPNG("./img/turtle_left1.png", screen);
	turtleImages[1] = loadPNG("./img/turtle_left2.png", screen);
	turtleImages[2] = loadPNG("./img/turtle_rigth1.png", screen);
	turtleImages[3] = loadPNG("./img/turtle_right2.png", screen);
}

void Turtle::draw(SDL_Surface* screen, int beginningOfCamera) {
	SDL_Surface* turtleImg = nullptr;
	turtleImg = turtleImages[this->model - 1];
	drawSurface(screen, turtleImg, this->positionX - beginningOfCamera, this->positionY);
}

void Turtle::move(Direction direction, int distance, World& world, Screen* mainScreen) {
	if (this->moveDirection != None && this->stepsCounter % 3 == 0) {
		if (isCharacterStandingOnTheBlock(this, world)) {
			int alignment = alignIfCollisionOccursDuringMovement(direction, distance, this, world);
			this->positionX += (direction == Right ? (distance - alignment) : -1 * (distance - alignment));
			if (alignment > 0) {
				this->moveDirection = (this->moveDirection == Right ? Left : Right);
				this->model = (this->moveDirection == Left ? 1 : 3);
			}
		}
		else {
			this->positionY += (2 * distance - alignIfCollisionOccursDuringVerticalMovement(Down, 2 * distance, this, world));
			this->positionX += (direction == Right ? 1 : -1) * (1 - alignIfCollisionOccursDuringMovement(direction, distance, this, world));
		}

		this->chooseModel();
	}
	++this->stepsCounter;
}

