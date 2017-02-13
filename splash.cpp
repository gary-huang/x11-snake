#include "splash.h"
#include <string>
#include <iostream>

using namespace std;

void SplashText::paint(XInfo &xInfo) {
	XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[0],
	 this->x, this->y, this->text.c_str(), this->text.length());
	//cout << text << endl;
}


void SplashText::unPaint(XInfo &xInfo) {
	XDrawString(xInfo.display, xInfo.pixmap, xInfo.gc[1],
	 this->x, this->y, this->text.c_str(), this->text.length());
	//cout << text << endl;
}


SplashText::SplashText(int x, int y, string text): x(x), y(y), text(text) {}

SplashText::~SplashText() {}
