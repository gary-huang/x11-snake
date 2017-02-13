#ifndef SNAKEBLOCK_H_
#define SNAKEBLOCK_H_

#include "displayable.h"
#include <iostream>

class SnakeBlock : public Displayable {
	public:
		virtual void paint(XInfo &xinfo);
		virtual void unPaint(XInfo &xinfo);
		int getX();

		int getY();

		void setX(int x);
		void setY(int y);

		SnakeBlock(int x, int y);
	private:
		int x;
		int y;
		int blockSize;
};

#endif