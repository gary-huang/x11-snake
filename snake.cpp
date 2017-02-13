#include "snake.h"
#include <cmath>

using namespace std;

void Snake::paint(XInfo &xinfo) {
	list<SnakeBlock *>::const_iterator begin = this->body->begin();
	list<SnakeBlock *>::const_iterator end = this->body->end();

	while( begin != end ) {
		SnakeBlock *b = *begin;
		b->paint(xinfo);
		begin++;			
	}
	/*
	for (int k = 0; k < length; ++k) {
		XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x - (k * blockSize), y, blockSize, blockSize);	
	}*/
	
}
		
void Snake::unPaint(XInfo &xinfo) {
	list<SnakeBlock *>::const_iterator begin = this->body->begin();
	list<SnakeBlock *>::const_iterator end = this->body->end();

	while( begin != end ) {
		SnakeBlock *b = *begin;
		b->unPaint(xinfo);
		begin++;			
	}
	/*
	for (int k = 0; k < length; ++k) {
		XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[1], x - (k * blockSize), y, blockSize, blockSize);	
	}*/
	
}
// true while still alive
bool Snake::move(XInfo &xinfo) {
	unPaint(xinfo);
	int deltaX = 0;
	int deltaY = 0;
	switch ( direction ) {
		case Up:
			deltaY = -moveFactor;
			break;
		case Down:
			deltaY = moveFactor;
			break;
		case Left:
			deltaX = -moveFactor;
			break;
		case Right:
			deltaX = moveFactor;
			break;
	}

	list<SnakeBlock *>::const_iterator begin = this->body->begin();
	list<SnakeBlock *>::const_iterator end = this->body->end();

	int lastX = (*begin)->getX();
	int lastY = (*begin)->getY();
	(*begin)->setX(lastX + deltaX);
	(*begin)->setY(lastY + deltaY);
	++begin;
	while( begin != end ) {
		SnakeBlock *b = *begin;
		int curX = b->getX();
		int curY = b->getY();
		b->setX(lastX);
		b->setY(lastY);
		lastX = curX;
		lastY = curY;
		begin++;	
	}
	didEatFruit(xinfo);
	return !this->didHitObstacle();
}

int Snake::getX() {
	return this->body->front()->getX();
}

int Snake::getY() {
	return this->body->front()->getY();
}

/*
 * ** ADD YOUR LOGIC **
 * Use these placeholder methods as guidance for implementing the snake behaviour. 
 * You do not have to use these methods, feel free to implement your own.
 */ 
void Snake::didEatFruit(XInfo &xInfo) {
	if ((abs(this->getX() - this->fruit->x) <= blockSize) && (abs(this->getY() - this->fruit->y) <= blockSize)) {
		this->fruit->regenerate(xInfo);
		int newX = this->body->back()->getX();
		int newY = this->body->back()->getY();
		//cout << newX << endl;
		//cout << newY << endl;
		switch ( direction ) {
			case Up:
				newY += blockSize;
				break;
			case Down:
				newY -= blockSize;
				break;
			case Left:
				newX += blockSize;
				break;
			case Right:
				newX -= blockSize;
				break;
		}
		//cout << newX << endl;
		//cout << newY << endl;
		body->push_back(new SnakeBlock(newX, newY));
		//++this->length;
		this->updateScore(blockSize, xInfo);
	}
}

void Snake::updateScore(int scoreToAdd, XInfo &xInfo) {
	this->score->unPaint(xInfo);
	this->score->addScore(scoreToAdd);
	this->score->paint(xInfo);
}

bool Snake::didHitObstacle() {
	// screen bound
	if ((this->getX() <= 0) || (this->getY() <= 0) || (this->getX() >= width) || (this->getY() >= height)) {
		return true;
	}

	// East self
	list<SnakeBlock *>::const_iterator begin = this->body->begin();
	list<SnakeBlock *>::const_iterator end = this->body->end();

	int headX = (*begin)->getX();
	int headY = (*begin)->getY();
	++begin;
	//++begin;
	while( begin != end ) {
		SnakeBlock *b = *begin;
		int curX = b->getX();
		int curY = b->getY();

		switch (direction) {
			case Up:
				if ((curY < headY) && 
					((curY - headY) <= 0) && 
					((curY - headY) >= -moveFactor) && 
					(abs(curX - headX) <= moveFactor)) 
					return true;
				break;
			case Down:
				if ((curY > headY) && 
					((headY - curY) <= 0) && 
					((headY - curY) >= -moveFactor) && 
					(abs(curX - headX) <= moveFactor)) 
					return true;
				break;
			case Left:
				if ((curX < headX) && 
					((curX - headX) <= 0) && 
					((curX - headX) >= -moveFactor) && 
					(abs(curY - headY) <= moveFactor)) 
					return true;
				break;
			case Right:
				if ((curX > headX) && 
					((headX - curX) <= 0) && 
					((headX - curX) >= -moveFactor) && 
					(abs(curY - headY) <= moveFactor)) 
					return true;
				break;
		}

						/*cout << "headX: " << headX << endl;
		cout << "headY: " << headY << endl;
		cout << "curX: " << curX << endl;
		cout << "curY: " << curY << endl;*/	

		begin++;	
	}
	return false;
}

void Snake::turnLeft() {
	if (direction == Up) direction = Left;
	else --direction;
}

void Snake::turnRight() {
	if (direction == Left) direction = Up;
	else ++direction;
}

Snake::Snake(int x, int y, Fruit *fruit, Score *score): fruit(fruit) {
	direction = Right;
	speed = 5;
    blockSize = 15;
    moveFactor = blockSize * (((float)speed / (float)10) + 1);
    body = new list<SnakeBlock *>();
    for (int k = 0; k < 5; ++k) {

    	body->push_back(new SnakeBlock(x - (k * blockSize), y));	
    	//		cout << "curX: " << this->body->back()->getX() << endl;
		//cout << "curY: " << this->body->back()->getY() << endl;
    }
    this->score = score;
}

void Snake::setSpeed(int speed) {
	this->speed = speed;
	this->moveFactor = this->blockSize * (((float)this->speed / (float)10) + 1);
}

int Snake::getSpeed() {
	return this->speed;
}

Snake::~Snake() {
	list<SnakeBlock *>::const_iterator begin = this->body->begin();
	list<SnakeBlock *>::const_iterator end = this->body->end();

	while( begin != end ) {
		SnakeBlock *b = *begin;
		delete(b);
		begin++;			
	}

	delete(this->body);
}