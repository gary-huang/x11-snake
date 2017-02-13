#ifndef SCORE_H_
#define SCORE_H_

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <string>
#include <iostream>
#include "splash.h"

using namespace std;

class Score : public SplashText {
	public:
		virtual void paint(XInfo &xinfo);
        virtual void unPaint(XInfo &xinfo);

        Score(int x, int y, string text);

        // ** ADD YOUR LOGIC **
        /*
         * The fruit needs to be re-generated at new location every time a snake eats it. See the assignment webpage for more details.
         */
        ~Score();

        void addScore(int scoreToAdd);
        int getScore();
    private:
        int score;
};

#endif