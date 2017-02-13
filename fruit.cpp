#include <X11/Xlib.h>
#include <X11/Xutil.h>

#include "fruit.h"
#include <stdlib.h>

using namespace std;

void Fruit::paint(XInfo &xinfo) {
	XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[0], x, y, 15, 15);
}

Fruit::Fruit(int maxX, int maxY) {
    //regenerateFruit();
    this->maxX = maxX - 200;
    this->maxY = maxY - 200;
    x = 250;
    y = 250;
}

void Fruit::regenerate(XInfo &xInfo) {
	unPaint(xInfo);
	this->x = (rand() % (maxX - 200)) + 200;
	this->y = (rand() % (maxY - 200)) + 200; // FIX THIS, GOING OUT OF BOUNDS RN
	cout << "X: " << x << "    Y:" << y << endl;
	cout << "maxX: " << maxX << "    maxY:" << maxY << endl;
	paint(xInfo);
}

void Fruit::unPaint(XInfo &xinfo) {
	XFillRectangle(xinfo.display, xinfo.pixmap, xinfo.gc[1], x, y, 15, 15);
}