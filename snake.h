#ifndef SNAKE_H_
#define SNAKE_H_

#include "displayable.h"
#include <iostream>
#include "fruit.h"
#include <list>
#include "snakeblock.h"
#include "score.h"

extern const int width;
extern const int height;

class Snake : public Displayable {
	public:
		virtual void paint(XInfo &xinfo);
		virtual void unPaint(XInfo &xinfo);

		bool move(XInfo &xinfo);
		
		int getX();

		int getY();

        /*
         * ** ADD YOUR LOGIC **
         * Use these placeholder methods as guidance for implementing the snake behaviour. 
         * You do not have to use these methods, feel free to implement your own.
         */ 
        void didEatFruit(XInfo &xInfo);

        bool didHitObstacle();

        void turnLeft();

        void turnRight();
		
		Snake(int x, int y, Fruit *fruit, Score *score);
		~Snake();

		void setSpeed(int speed);
		int getSpeed();

		void updateScore(int scoreToAdd, XInfo &xInfo);
	private:
		int x;
		int y;
		std::list<SnakeBlock *> *body;
		int blockSize;
		int moveFactor;
		int direction;
		int speed;
		int length;
		Fruit *fruit;
		Score *score;
		enum {
			Up = 0,
			Right = 1,
			Down = 2,
			Left = 3
		};
};

#endif

