#include "snakeblock.h"

using namespace std;

void SnakeBlock::paint(XInfo &xinfo) {
	/*
	unsigned int retWidth = 20;
	unsigned int retHeight = 20;
	int depth = DefaultDepth(xinfo.display, DefaultScreen(xinfo.display));
	Pixmap taytay = XCreatePixmap(xinfo.display, xinfo.pixmap, retWidth, retHeight, depth);
	int *hotx, *hoty;
	XReadBitmapFile(xinfo.display, xinfo.pixmap, "taytay.xmb", &retWidth, &retHeight, 
		&taytay, hotx, hoty);
	XCopyArea(xinfo.display, taytay, xinfo.pixmap, xinfo.gc[1], 0, 0, retWidth, retHeight, 0, 0);*/
	XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, blockSize, blockSize);	
}
void SnakeBlock::unPaint(XInfo &xinfo) {

	XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, y, blockSize, blockSize);	
}

int SnakeBlock::getX() {
	return this->x;
}

int SnakeBlock::getY() {
	return this->y;
}

void SnakeBlock::setX(int x) {
	//cout << "X: " << x << endl
	this->x = x;
}

void SnakeBlock::setY(int y) {
	//cout << "Y: " << y << endl;
	this->y = y;
}

SnakeBlock::SnakeBlock(int x, int y): x(x), y(y) {
	this->blockSize = 15;
}