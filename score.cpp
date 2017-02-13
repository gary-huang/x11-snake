#include <string>
#include "score.h"
#include <sstream>

using namespace std;

void Score::paint(XInfo &xinfo) {
	stringstream ss;
	ss << "Score: " << this->score;

	this->text = ss.str();
	SplashText::paint(xinfo);
}

void Score::unPaint(XInfo &xinfo) {
	SplashText::unPaint(xinfo);
}

Score::Score(int x, int y, string text):SplashText::SplashText(x, y, text) {
	this->score = 0;
}


void Score::addScore(int scoreToAdd) {
	this->score += scoreToAdd;
}

int Score::getScore() {
	return this->score;
}